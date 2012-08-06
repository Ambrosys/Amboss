if ( NOT SQLITE3_FOUND )
  message(FATAL_ERROR "Sqlite3 required here, but not found!")
endif( NOT SQLITE3_FOUND )

include_directories ( ${gtest_SOURCE_DIR}/include )
include_directories ( ${gtest_SOURCE_DIR} )
include_directories ( ${SQLITE3_INCLUDE_DIR} )

add_executable ( Sqlite3Tests Sqlite3DB.cpp )

MESSAGE( STATUS "${SQLITE3_LIBRARY}" )

target_link_libraries ( Sqlite3Tests gtest gtest_main ${SQLITE3_LIBRARY} )

add_custom_command(TARGET Sqlite3Tests POST_BUILD COMMAND Sqlite3Tests )
