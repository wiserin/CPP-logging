set(LOGGER_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp)


target_sources(WiseLogging PRIVATE ${LOGGER_SRC_FILES})
