set(SYNC_IO_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/fileio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stdio.cpp)


target_sources(WiseLogging PRIVATE ${SYNC_IO_SRC_FILES})
