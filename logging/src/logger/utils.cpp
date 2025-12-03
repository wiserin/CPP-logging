#include <string>  // Copyright 2025 wiserin
#include <utility>

#include "logging/logger.hpp"
#include "logging/schemas.hpp"
#include "iocontroller.hpp"


using str = std::string;


namespace logging {

Log Logger::BuildLog(const str& log, LoggerMode badge, Priority priority) const {
    str data = GetBadge(badge) + ' ' + logger_name + ' ' + log;
    Log compl_log {std::move(data), priority};
    return compl_log;
}

bool Logger::CheckLevel(LoggerMode log_mode) const {
    if (static_cast<int>(log_mode) >= static_cast<int>(mode)) {
        return true;
    } else {
        return false;
    }
}

const str& Logger::GetBadge(LoggerMode log_mode) const {
    switch (log_mode) {
        case logging::LoggerMode::kDebug : {
            if (colored) {
                return ColoredBadges::kDebug;
            } else {
                return Badges::kDebug;
            }
            break;
        }
        case logging::LoggerMode::kInfo : {
            if (colored) {
                return ColoredBadges::kInfo;
            } else {
                return Badges::kInfo;
            }
            break;
        }
        case logging::LoggerMode::kWarning : {
            if (colored) {
                return ColoredBadges::kWarning;
            } else {
                return Badges::kWarning;
            }
            break;
        }
        case logging::LoggerMode::kException : {
            if (colored) {
                return ColoredBadges::kException;
            } else {
                return Badges::kException;
            }
            break;
        }
        case logging::LoggerMode::kError : {
            if (colored) {
                return ColoredBadges::kError;
            } else {
                return Badges::kError;
            }
            break;
        }
        case logging::LoggerMode::kCritical : {
            if (colored) {
                return ColoredBadges::kCritical;
            } else {
                return Badges::kCritical;
            }
            break;
        }
    }
}

}  // namespace logging
