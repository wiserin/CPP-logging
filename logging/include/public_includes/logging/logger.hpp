#pragma once  // Copyright 2025 wiserin
#include <string>
#include <memory>

#include "logging/schemas.hpp"
#include "iocontroller.hpp"


using str = std::string;

namespace logging {

class Logger {
    static LoggerMode mode;
    static std::unique_ptr<IOController> controller;
    static bool colored;

    str logger_name;

    bool CheckLevel(LoggerMode log_mode) const;
    Log BuildLog(const str& log, LoggerMode mode, Priority proirity) const;

    const str& GetBadge(LoggerMode log_mode) const;

 public:
    static void SetupLogger(
        const str& file_path,
        LoggerMode logging_level,
        LoggerIOMode io_mode = LoggerIOMode::kSync,
        bool colored = false);

    static void SetupLogger(
        LoggerMode logging_level,
        LoggerIOMode io_mode = LoggerIOMode::kSync,
        bool colored = false);

    Logger() = default;
    Logger(Logger&& logger);
    Logger& operator=(Logger&& logger);
    explicit Logger(str&& name);

    void DisableBuff();

    void Debug(str&& log) const;
    void Info(str&& log) const;
    void Warning(str&& log) const;
    void Exception(str&& log) const;
    void Error(str&& log) const;
    void Critical(str&& log) const;
};

}  // namespace logging
