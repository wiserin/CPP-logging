add_library(logging STATIC)

target_include_directories(logging PUBLIC include/public_includes)
target_include_directories(logging PRIVATE include/private_includes)

add_subdirectory(src)
