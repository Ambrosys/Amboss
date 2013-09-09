find_package ( Git )

if ( NOT EXISTS "${CMAKE_SOURCE_DIR}/.git/" )
  return ()
endif ()

execute_process ( COMMAND git describe --abbrev=4 HEAD
                  COMMAND sed -e "s/-/./g"
                  OUTPUT_VARIABLE AMBOSS_GIT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE )
                  
execute_process ( COMMAND git status -uno -s 
                  OUTPUT_VARIABLE AMBOSS_GIT_STATUS 
                  OUTPUT_STRIP_TRAILING_WHITESPACE )


string ( REGEX REPLACE "^v([0-9]+)\\..*" "\\1" AMBOSS_VERSION_MAJOR "${AMBOSS_GIT_VERSION}" )
string ( REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" AMBOSS_VERSION_MINOR "${AMBOSS_GIT_VERSION}" )
string ( REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" AMBOSS_VERSION_PATCH "${AMBOSS_GIT_VERSION}" )
string ( REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+.(.*)" "\\1" AMBOSS_VERSION_SHA1 "${AMBOSS_GIT_VERSION}" )

if ( ${AMBOSS_VERSION_PATCH} STREQUAL ${AMBOSS_GIT_VERSION} )
  set ( AMBOSS_VERSION_PATCH "0" )
  set ( AMBOSS_VERSION_SHA1 "0" )
endif ()

math ( EXPR AMBOSS_VERSION_PATCH "${AMBOSS_VERSION_PATCH} + 1" )

set ( AMBOSS_VERSION_SHORT "${AMBOSS_VERSION_MAJOR}.${AMBOSS_VERSION_MINOR}.${AMBOSS_VERSION_PATCH}" )

# message ( STATUS "${AMBOSS_VERSION_MAJOR}" )
# message ( STATUS "${AMBOSS_VERSION_MINOR}" )
# message ( STATUS "${AMBOSS_VERSION_PATCH}" )
# message ( STATUS "${AMBOSS_VERSION_SHA1}" )
# message ( STATUS "${AMBOSS_VERSION_SHORT}" )

if ( NOT ( AMBOSS_GIT_STATUS STREQUAL "" ) )

  message ( STATUS "generating new config_version.hpp" )
  configure_file ( ${CMAKE_SOURCE_DIR}/include/Amboss/AmbossVersion.h.cmake ${CMAKE_SOURCE_DIR}/include/Amboss/AmbossVersion.h )

endif ()

