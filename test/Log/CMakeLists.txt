
include_directories ( ${gtest_SOURCE_DIR}/include )
include_directories ( ${gtest_SOURCE_DIR} )

add_executable ( LogTests LogEntry.cpp OStreamLogger.cpp LoggerCollection.cpp LogEntryStream.cpp OStreamLoggerMT.cpp ThreadingModel.cpp )

target_link_libraries ( LogTests gtest gtest_main )

# add_custom_command(TARGET LogTests POST_BUILD COMMAND LogTests )
add_test( NAME LogTests COMMAND LogTests )