#include <stdexcept>  // Copyright 2025 wiserin
#include <string>
#include <memory>
#include <utility>

#include <logging/logger.hpp>
#include <logging/schemas.hpp>
#include <iocontroller.hpp>


using str = std::string;


namespace logging {

LoggerMode Logger::mode;
std::unique_ptr<IOController> Logger::controller = nullptr;
bool Logger::colored;


void Logger::SetupLogger(
        const str& file_path,
        LoggerMode input_mode,
        LoggerIOMode io_mode,
        bool is_colored) {
    if (io_mode == LoggerIOMode::kAsync) {
        controller = std::make_unique<AsyncFileIOController>(file_path);
    } else {
        controller = std::make_unique<SyncFileIOController>(file_path);
    }
    mode = input_mode;
    colored = is_colored;
}


void Logger::SetupLogger(
    LoggerMode input_mode,
    LoggerIOMode io_mode,
    bool is_colored) {
    if (io_mode == LoggerIOMode::kAsync) {
        controller = std::make_unique<AsyncStdIOController>();
    } else {
        controller = std::make_unique<SyncStdIOController>();
    }
    mode = input_mode;
    colored = is_colored;
}


Logger::Logger(str&& name) {
    if (controller == nullptr) {
        throw std::runtime_error("Необходима инициализация логгера");
    }
    logger_name = std::move(name);
    logger_name = logger_name + " ";
}

Logger::Logger(Logger&& logger) {
    logger_name = std::move(logger.logger_name);
}

void Logger::DisableBuff() {
    controller->TurnOfOutBuff();
}

}  // namespace logging
