
include_directories ( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )


add_executable ( TestMain GeometryTest.cpp PlacemarkTest.cpp FolderTest.cpp DocumentTest.cpp BoostGeometryTest.cpp )

target_link_libraries ( TestMain gtest gtest_main )


add_custom_command(TARGET TestMain POST_BUILD COMMAND TestMain)
