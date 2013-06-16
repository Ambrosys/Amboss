
include_directories ( ${gtest_SOURCE_DIR}/include )
include_directories ( ${gtest_SOURCE_DIR} )
include_directories ( ${gmock_SOURCE_DIR} )
include_directories ( ${gmock_SOURCE_DIR}/include )


add_executable ( ThreadTests ThreadPool.cpp FunctionWrapper.cpp )

target_link_libraries ( ThreadTests gtest gtest_main gmock )

# add_custom_command( TARGET ThreadPoolTests POST_BUILD COMMAND ThreadPoolTests )
add_test( NAME ThreadTests COMMAND ThreadTests )