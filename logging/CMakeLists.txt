add_library(logging STATIC)

target_include_directories(
    logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/public_includes)
target_include_directories(
    logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/private_includes)

add_subdirectory(src)
