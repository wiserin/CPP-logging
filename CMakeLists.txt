# Мне лень добавлять его в gitignore

cmake_minimum_required(VERSION 3.12)

project(
    logging
    VERSION 1.0
    DESCRIPTION "Simple logger"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(logging)