#include <memory>  // Copyright 2025 wiserin
#include <utility>

#include "logging/logger.hpp"
#include "logging/schemas.hpp"
#include "iocontroller.hpp"



namespace logging {

void Logger::Debug(str&& log) const {
    if (CheckLevel(LoggerMode::kDebug)) {
        Log local_log = BuildLog(log, LoggerMode::kDebug, Priority::kHigh);
        controller->AddLog(std::move(local_log));
    }
}


void Logger::Info(str&& log) const {
    if (CheckLevel(LoggerMode::kInfo)) {
        Log local_log = BuildLog(log, LoggerMode::kInfo, Priority::kLow);
        controller->AddLog(std::move(local_log));
    }
}


void Logger::Warning(str&& log) const {
    if (CheckLevel(LoggerMode::kWarning)) {
        Log local_log = BuildLog(log, LoggerMode::kWarning, Priority::kNormal);
        controller->AddLog(std::move(local_log));
    }
}


void Logger::Exception(str&& log) const {
    if (CheckLevel(LoggerMode::kException)) {
        Log local_log = BuildLog(log, LoggerMode::kException, Priority::kHigh);
        controller->AddLog(std::move(local_log));
    }
}


void Logger::Error(str&& log) const {
    if (CheckLevel(LoggerMode::kError)) {
        Log local_log = BuildLog(log, LoggerMode::kError, Priority::kHigh);
        controller->AddLog(std::move(local_log));
    }
}


void Logger::Critical(str&& log) const {
    if (CheckLevel(LoggerMode::kCritical)) {
        Log local_log = BuildLog(log, LoggerMode::kCritical, Priority::kMax);
        controller->AddLog(std::move(local_log));
    }
}


}  // namespace logging
