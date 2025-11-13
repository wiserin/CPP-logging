#include <ios>  // Copyright 2025 wiserin
#include <string>
#include <iostream>

#include <iocontroller.hpp>

using str = std::string;


void StdIOController::WriteLine(const str& str_to_write) {
    std::cout << str_to_write << '\n';
}

void StdIOController::TurnOfOutBuff() {
    std::cout << std::unitbuf;
}

