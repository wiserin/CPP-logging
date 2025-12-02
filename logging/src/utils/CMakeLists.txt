set(UTILS_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/queue.cpp)

add_subdirectory(io)

target_sources(WiseLogging PRIVATE ${UTILS_SRC_FILES})
