project (AMBOSS)
cmake_minimum_required (VERSION 2.6) 

# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
  )

find_package (Boost REQUIRED)
find_package( GDAL )



if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++0x")        ## Optimize
endif()

include_directories ( ${AMBOSS_SOURCE_DIR}/include )
include_directories ( ${Boost_INCLUDE_DIRS} )


if(IS_DIRECTORY gtest)
  add_subdirectory (gtest)
  enable_testing(true)

  add_subdirectory (test/KML)
  add_subdirectory (test/Shapefile)
else()
  message(WARNING "gtest directory not found. Unit tests will not be performed. Download googletest and put it in a directory gtest in the main directory.")
endif()




add_subdirectory (examples/KML)
add_subdirectory (examples/Shapefile)
