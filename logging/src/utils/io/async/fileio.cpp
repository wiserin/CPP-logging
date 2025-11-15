#include <exception>  // Copyright 2025 wiserin
#include <ios>
#include <stdexcept>
#include <string>
#include <fstream>
#include <mutex>
#include <thread>
#include <utility>
#include <iostream>

#include <iocontroller.hpp>
#include <utils.hpp>

using str = std::string;


AsyncFileIOController::AsyncFileIOController(const str& file_path) {
    file.open(file_path, std::ios::app);
    if (!file) {
        throw std::runtime_error("Не получилось открыть требуемый файл");
    }
    worker = std::thread(&AsyncFileIOController::WriterRunner, this);

    std::unique_lock<std::mutex> lock(mut);
    started_cv.wait(lock, [this]{ return is_started; });
}


void AsyncFileIOController::WriterStarted() {
    std::unique_lock<std::mutex> lock(mut);
    is_started = true;
    started_cv.notify_one();
}


void AsyncFileIOController::WriterRunner() {
    try {
        WriterStarted();
        while (!is_stop) {
            std::unique_lock<std::mutex> lock(mut);
            cv.wait(lock, [this](){ return is_stop || !log_queue.IsEmpty(); });

            while (!log_queue.IsEmpty()) {
                Write(lock);
            }

            if (is_stop && log_queue.IsEmpty()) {
                return;
            }
        }
    } catch (const std::exception& ex) {
        std::unique_lock<std::mutex> lock(mut);
        is_error = true;
        error_text = std::move(ex.what());
        return;
    }
}


void AsyncFileIOController::Write(std::unique_lock<std::mutex>& lock) {
    if (!file) {
        throw std::runtime_error("Ошибка при получении доступа к файлу при записи");
    }

    logging::Log log_to_write = log_queue.Pop();
    lock.unlock();

    file << log_to_write.log << '\n';

    if (file.fail()) {
        throw std::runtime_error("Не получилось записать строку в файл");
    }
    lock.lock();
}


void AsyncFileIOController::AddLog(logging::Log&& log) {
    std::unique_lock<std::mutex> lock(mut);
    log_queue.Push(std::move(log));
    cv.notify_one();
}


void AsyncFileIOController::TurnOfOutBuff() {
    file.rdbuf()->pubsetbuf(0, 0);
}


AsyncFileIOController::~AsyncFileIOController() {
    {
        std::unique_lock<std::mutex> lock(mut);
        is_stop = true;
    }
    cv.notify_one();
    worker.join();

    if (file) {
        file.close();
    }
    if (is_error) {
        std::cerr << error_text << std::endl;
    }
}
