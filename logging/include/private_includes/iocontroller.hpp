#pragma once  // Copyright 2025 wiserin
#include <fstream>
#include <string>


using str = std::string;

class IOController {
 public:
    virtual void WriteLine(const str& str_to_write) = 0;

    virtual void TurnOfOutBuff() = 0;

    virtual ~IOController() = default;
};

class FileIOController : public IOController {
    std::ofstream file;

 public:
    explicit FileIOController(str file_path);

    void WriteLine(const str& str_to_write) override;

    void TurnOfOutBuff() override;

    ~FileIOController();
};


class StdIOController : public IOController {
 public:
    StdIOController() = default;

    void WriteLine(const str& str_to_write) override;

    void TurnOfOutBuff() override;

    ~StdIOController() = default;
};
