project (AMBOSS)
cmake_minimum_required (VERSION 2.6) 


# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
  )


if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++0x")        ## Optimize
endif()

include_directories ( ${AMBOSS_SOURCE_DIR}/include )

add_subdirectory (test/KML)
# add_subdirectory (src) 
