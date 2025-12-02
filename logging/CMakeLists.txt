add_library(WiseLogging SHARED)

target_include_directories(
    WiseLogging PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public_includes)
target_include_directories(
    WiseLogging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/private_includes)

add_subdirectory(src)
