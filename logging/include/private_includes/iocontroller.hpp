#pragma once  // Copyright 2025 wiserin
#include <condition_variable>
#include <fstream>
#include <string>
#include <mutex>
#include <thread>

#include <logging/schemas.hpp>
#include <utils.hpp>


using str = std::string;

class IOController {
 public:
    virtual void AddLog(Log&& log) = 0;

    virtual void TurnOfOutBuff() = 0;

    virtual ~IOController() = default;
};


class FileIOController : public IOController {
    std::mutex mut;
    std::condition_variable cv;
    std::condition_variable started_cv;
    std::thread worker;

    std::ofstream file;
    WorkerQueue<Log, LogComparator> log_queue;

    bool is_stop = false;
    bool is_started = false;
    bool is_error = false;

    str error_text;

    void WriterRunner();
    void WriterStarted();
    void Write(std::unique_lock<std::mutex>& lock);

 public:
    explicit FileIOController(const str& file_path);

    void AddLog(Log&& log) override;

    void TurnOfOutBuff() override;

    ~FileIOController();
};


class StdIOController : public IOController {
    std::condition_variable cv;
    std::mutex mut;
    std::thread worker;

    WorkerQueue<Log, LogComparator> log_queue;

    bool is_stop = false;

    void WriterRunner();
    void Write(std::unique_lock<std::mutex>& lock);

 public:
    StdIOController();

    void AddLog(Log&& log) override;

    void TurnOfOutBuff() override;

    ~StdIOController();
};
