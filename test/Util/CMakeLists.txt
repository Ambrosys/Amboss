
include_directories ( ${gtest_SOURCE_DIR}/include )
include_directories ( ${gtest_SOURCE_DIR} )


add_executable ( UtilTests ValueType.cpp Version.cpp ProcessIndependentTimer.cpp )

target_link_libraries ( UtilTests gtest gtest_main )

# add_custom_command(TARGET UtilTests POST_BUILD COMMAND UtilTests )
add_test( NAME UtilTests COMMAND UtilTests )