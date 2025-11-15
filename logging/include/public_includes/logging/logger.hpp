#pragma once  // Copyright 2025 wiserin
#include <string>
#include <memory>

#include <logging/schemas.hpp>
#include <iocontroller.hpp>


using str = std::string;

namespace logging {

class Logger {
    static LoggerMode mode;
    static std::unique_ptr<IOController> controller;

    str logger_name;

    const str info_badge = "[INFO] ";

 public:
    static void SetupLogger(
        const str& file_path,
        LoggerMode mode,
        LoggerIOMode io_mode = LoggerIOMode::kSync);

    static void SetupLogger(
        LoggerMode mode,
        LoggerIOMode io_mode = LoggerIOMode::kSync);

    explicit Logger(str&& name);

    void Info(str&& log);
};

}  // namespace logging
