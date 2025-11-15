#pragma once  // Copyright 2025 wiserin
#include <string>
#include <memory>

#include <logging/schemas.hpp>
#include <iocontroller.hpp>


using str = std::string;


class Logger {
    static LoggerMode mode;
    static std::unique_ptr<IOController> controller;

    str logger_name;

    const str info_badge = "[INFO] ";

 public:
    static void SetupLogger(const str& file_path, LoggerMode mode);

    static void SetupLogger(LoggerMode mode);

    explicit Logger(str&& name);

    void Info(str&& log);
};
