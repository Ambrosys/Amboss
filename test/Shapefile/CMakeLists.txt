if ( NOT GDAL_FOUND )
  message(FATAL_ERROR "GDAL required here, but not found!")
endif( NOT GDAL_FOUND )

include_directories ( ${gtest_SOURCE_DIR}/include )
include_directories ( ${gtest_SOURCE_DIR} )
include_directories ( ${GDAL_INCLUDE_DIR} )

add_executable ( ShapefileTests Shapefile.cpp )

target_link_libraries ( ShapefileTests gtest gtest_main ${GDAL_LIBRARY} )

# add_custom_command(TARGET ShapefileTests POST_BUILD COMMAND ShapefileTests )
add_test( NAME ShapefileTests COMMAND ShapefileTests )


set ( AMBOSS_SHAPEFILE_TEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/samples )

configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/ShapefileTestConfig.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/ShapefileTestConfig.h )