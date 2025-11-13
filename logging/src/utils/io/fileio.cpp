#include <ios>  // Copyright 2025 wiserin
#include <stdexcept>
#include <string>
#include <fstream>

#include <iocontroller.hpp>

using str = std::string;


FileIOController::FileIOController(str file_path) {
    file.open(file_path, std::ios::app);
    if (!file) {
        throw std::runtime_error("Не получилось открыть требуемый файл");
    }
}


void FileIOController::WriteLine(const str& str_to_write) {
    if (!file) {
        throw std::runtime_error("Ошибка при получении доступа к файлу при записи");
    }

    file << str_to_write << '\n';

    if (file.fail()) {
        throw std::runtime_error("Не получилось записать строку в файл");
    }
}


void FileIOController::TurnOfOutBuff() {
    file.rdbuf()->pubsetbuf(0, 0);
}


FileIOController::~FileIOController() {
    if (file) {
        file.close();
    }
}
