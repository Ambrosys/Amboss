find_package( GDAL REQUIRED)

include_directories ( ${gtest_SOURCE_DIR}/include )
include_directories ( ${gtest_SOURCE_DIR} )
include_directories ( ${GDAL_INCLUDE_DIR} )

add_executable ( ShapefileTests Shapefile.cpp )

target_link_libraries ( ShapefileTests gtest gtest_main ${GDAL_LIBRARY} )

add_custom_command(TARGET ShapefileTests POST_BUILD COMMAND ShapefileTests )
