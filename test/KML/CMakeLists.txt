find_package(CppUnit REQUIRED)

include_directories ( ${CPPUNIT_INCLUDE_DIR} )


add_executable ( TestMain Main.cpp KMLEntityTest.cpp KMLWriterTest.cpp )
target_link_libraries ( TestMain ${CPPUNIT_LIBRARY} )


add_custom_command(TARGET TestMain POST_BUILD COMMAND TestMain)
