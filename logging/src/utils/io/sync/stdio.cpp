#include <ios>  // Copyright 2025 wiserin
#include <string>
#include <iostream>
#include <utility>

#include "iocontroller.hpp"

using str = std::string;


void SyncStdIOController::AddLog(logging::Log&& log) {
    logging::Log log_to_write = std::move(log);
    std::cout << log_to_write.log << '\n';
}


void SyncStdIOController::TurnOfOutBuff() {
    std::cout << std::unitbuf;
}
