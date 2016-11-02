
project (AMBOSS)

cmake_minimum_required (VERSION 2.8) 

set ( CMAKE_CXX_FLAGS "-std=c++11" )

set( SQLITE_DEFAULT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sqlite3 )


# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
  )
  
include ( CreateVersionFile )
message ( STATUS "Building project ${CMAKE_PROJECT_NAME}" )
message ( STATUS "Version: ${AMBOSS_VERSION_SHORT}" )


find_package (Boost REQUIRED)
find_package (GDAL)
find_package (Sqlite3 REQUIRED)



# if(CMAKE_COMPILER_IS_GNUCXX)
#    set(CMAKE_CXX_FLAGS "-std=c++0x")        ## Optimize
# endif()

include_directories ( ${AMBOSS_SOURCE_DIR}/include )
include_directories ( ${Boost_INCLUDE_DIRS} )


if ( IS_DIRECTORY ${AMBOSS_SOURCE_DIR}/gtest/include AND IS_DIRECTORY ${AMBOSS_SOURCE_DIR}/gmock/include )
 
  message( STATUS "gtest and gmock directories found. Unit tests are enabled." )
   
  include_directories ( gtest gtest/include gmock gmock/include )
  
  add_library ( gtest gtest/src/gtest-all.cc )
  target_link_libraries ( gtest pthread )
  add_library ( gtest_main gtest/src/gtest_main.cc )
  add_library ( gmock gmock/src/gmock-all.cc )
  
  enable_testing(true)

  add_subdirectory ( test/KML )
  add_subdirectory ( test/Shapefile )
  add_subdirectory ( test/Sqlite3 )
  add_subdirectory ( test/Log )
  add_subdirectory ( test/Util )
  add_subdirectory ( test/Thread )
  
else()

  message( WARNING "gtest and/or gmock directories not found. Unit tests will not be performed. Download googletest and googlemock and put it in the directories gtest and gmock respectively inside the main directory or use git submodule update --init" )

endif()



add_subdirectory (examples/KML)
add_subdirectory (examples/Shapefile)
