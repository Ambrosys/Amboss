if ( NOT SQLITE3_FOUND )
  message(FATAL_ERROR "Sqlite3 required here, but not found!")
endif( NOT SQLITE3_FOUND )

include_directories ( ${gtest_SOURCE_DIR}/include )
include_directories ( ${gtest_SOURCE_DIR} )
include_directories ( ${SQLITE3_INCLUDE_DIR} )

add_executable ( Sqlite3Tests Sqlite3DB.cpp )

target_link_libraries ( Sqlite3Tests gtest gtest_main ${SQLITE3_LIBRARY} )

# add_custom_command(TARGET Sqlite3Tests POST_BUILD COMMAND Sqlite3Tests )
add_test( NAME Sqlite3Tests COMMAND Sqlite3Tests )

set ( AMBOSS_SQLITE_SAMPLE_DB ${CMAKE_CURRENT_SOURCE_DIR}/sample.db )

configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/Sqlite3TestConfig.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/Sqlite3TestConfig.h )