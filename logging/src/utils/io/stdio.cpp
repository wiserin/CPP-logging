#include <ios>  // Copyright 2025 wiserin
#include <mutex>
#include <string>
#include <iostream>
#include <thread>
#include <utility>

#include <iocontroller.hpp>
#include <utils.hpp>


using str = std::string;

StdIOController::StdIOController() {
    worker = std::thread(&StdIOController::WriterRunner, this);
}


void StdIOController::WriterRunner() {
    while (!is_stop) {
        std::unique_lock<std::mutex> lock(mut);

        cv.wait(lock, [this](){ return is_stop || !log_queue.IsEmpty(); });
        std::cout << "Here 3" << std::endl;

        if (is_stop) {
            return;
        } else {
            std::cout << "in while" << std::endl;
            while (!log_queue.IsEmpty()) {
                Write(lock);
            }
        }
    }
}


void StdIOController::Write(std::unique_lock<std::mutex>& lock) {
    Log log_to_write = log_queue.Pop();
    lock.unlock();

    std::cout << log_to_write.log << '\n';

    lock.lock();
}


void StdIOController::AddLog(Log&& log) {
    std::unique_lock<std::mutex> lock(mut);
    log_queue.Push(std::move(log));
    cv.notify_one();
}


void StdIOController::TurnOfOutBuff() {
    std::cout << std::unitbuf;
}


StdIOController::~StdIOController() {
    {
        std::unique_lock<std::mutex> lock(mut);
        is_stop = true;
    }
    cv.notify_one();
    worker.join();
}

