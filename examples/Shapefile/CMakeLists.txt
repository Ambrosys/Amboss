if ( NOT GDAL_FOUND )
  message(FATAL_ERROR "GDAL required here, but not found!")
endif( NOT GDAL_FOUND )


include_directories ( ${GDAL_INCLUDE_DIR} )

# add_executable ( ShapefileTests Shapefile.cpp )
# target_link_libraries ( ShapefileTests gtest gtest_main ${GDAL_LIBRARY} )


