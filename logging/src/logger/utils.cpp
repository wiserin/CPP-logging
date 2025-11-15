#include <string>  // Copyright 2025 wiserin
#include <utility>

#include <logging/logger.hpp>
#include <logging/schemas.hpp>
#include <iocontroller.hpp>


using str = std::string;


namespace logging {

Log Logger::BuildLog(const str& log, const str& badge, Priority priority) {
    str data = badge + ' ' + logger_name + ' ' + log;
    Log compl_log {std::move(data), priority};
    return compl_log;
}

bool Logger::CheckLevel(LoggerMode log_mode) {
    if (static_cast<int>(log_mode) >= static_cast<int>(mode)) {
        return true;
    } else {
        return false;
    }
}

}  // namespace logging
