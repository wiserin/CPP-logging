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
    virtual void AddLog(logging::Log&& log) = 0;

    virtual void TurnOfOutBuff() = 0;

    virtual ~IOController() = default;
};


class AsyncFileIOController : public IOController {
    std::mutex mut;
    std::condition_variable cv;
    std::condition_variable started_cv;
    std::thread worker;

    std::ofstream file;
    WorkerQueue<logging::Log, LogComparator> log_queue;

    bool is_stop = false;
    bool is_started = false;
    bool is_error = false;

    str error_text;

    void WriterRunner();
    void WriterStarted();
    void Write(std::unique_lock<std::mutex>& lock);

 public:
    explicit AsyncFileIOController(const str& file_path);

    void AddLog(logging::Log&& log) override;

    void TurnOfOutBuff() override;

    ~AsyncFileIOController();
};


class AsyncStdIOController : public IOController {
    std::condition_variable cv;
    std::condition_variable started_cv;
    std::mutex mut;
    std::thread worker;

    WorkerQueue<logging::Log, LogComparator> log_queue;

    bool is_stop = false;
    bool is_started = false;
    bool is_error = false;

    str error_text;

    void WriterRunner();
    void WriterStarted();
    void Write(std::unique_lock<std::mutex>& lock);

 public:
    AsyncStdIOController();

    void AddLog(logging::Log&& log) override;

    void TurnOfOutBuff() override;

    ~AsyncStdIOController();
};


class SyncFileIOController : public IOController {
    std::ofstream file;

 public:
    explicit SyncFileIOController(const str& file_path);

    void AddLog(logging::Log&& log) override;

    void TurnOfOutBuff() override;

    ~SyncFileIOController();
};


class SyncStdIOController : public IOController {
 public:
    explicit SyncStdIOController() = default;

    void AddLog(logging::Log&& log) override;

    void TurnOfOutBuff() override;

    ~SyncStdIOController() = default;
};
