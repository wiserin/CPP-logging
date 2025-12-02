#include <ios>  // Copyright 2025 wiserin
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

#include "iocontroller.hpp"

using str = std::string;


SyncFileIOController::SyncFileIOController(const str& file_path) {
    file.open(file_path, std::ios::app);
    if (!file) {
        throw std::runtime_error("Не получилось открыть требуемый файл");
    }
}


void SyncFileIOController::AddLog(logging::Log&& log) {
    if (!file) {
        throw std::runtime_error("Ошибка при получении доступа к файлу при записи");
    }

    logging::Log log_to_write = std::move(log);

    file << log_to_write.log << '\n';

    if (file.fail()) {
        throw std::runtime_error("Не получилось записать строку в файл");
    }
}


void SyncFileIOController::TurnOfOutBuff() {
    file.rdbuf()->pubsetbuf(0, 0);
}


SyncFileIOController::~SyncFileIOController() {
    if (file) {
        file.close();
    }
}
