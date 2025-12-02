#include <ios>  // Copyright 2025 wiserin
#include <mutex>
#include <string>
#include <iostream>
#include <thread>
#include <utility>

#include "iocontroller.hpp"
#include "utils.hpp"


using str = std::string;

AsyncStdIOController::AsyncStdIOController() {
    worker = std::thread(&AsyncStdIOController::WriterRunner, this);

    std::unique_lock<std::mutex> lock(mut);
    started_cv.wait(lock, [this]{ return is_started; });
}


void AsyncStdIOController::WriterStarted() {
    std::unique_lock<std::mutex> lock(mut);
    is_started = true;
    started_cv.notify_one();
}


void AsyncStdIOController::WriterRunner() {
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


void AsyncStdIOController::Write(std::unique_lock<std::mutex>& lock) {
    logging::Log log_to_write = log_queue.Pop();
    lock.unlock();

    std::cout << log_to_write.log << '\n';

    lock.lock();
}


void AsyncStdIOController::AddLog(logging::Log&& log) {
    std::unique_lock<std::mutex> lock(mut);
    log_queue.Push(std::move(log));
    cv.notify_one();
}


void AsyncStdIOController::TurnOfOutBuff() {
    std::cout << std::unitbuf;
}


AsyncStdIOController::~AsyncStdIOController() {
    {
        std::unique_lock<std::mutex> lock(mut);
        is_stop = true;
    }
    cv.notify_one();
    worker.join();
    if (is_error) {
        std::cerr << error_text << std::endl;
    }
}

