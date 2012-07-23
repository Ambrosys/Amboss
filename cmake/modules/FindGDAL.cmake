#
# http://root.cern.ch/viewvc/trunk/cint/reflex/cmake/modules/FindCppUnit.cmake
#
# - Find CppUnit
# This module finds an installed CppUnit package.
#
# It sets the following variables:
#  GDAL_FOUND       - Set to false, or undefined, if CppUnit isn't found.
#  GDAL_INCLUDE_DIR - The Gdal include directory.
#  GDAL_LIBRARY - The Gdal library.


SET(GDAL_ROOT $ENV{GDAL_ROOT})

FIND_PATH(GDAL_INCLUDE_DIR gdal.h ${GDAL_ROOT}/include )
FIND_LIBRARY(GDAL_LIBRARY NAMES gdal PATHS ${GDAL_ROOT}/lib )

IF (GDAL_INCLUDE_DIR AND GDAL_LIBRARY)
   SET(GDAL_FOUND TRUE)
ENDIF (GDAL_INCLUDE_DIR AND GDAL_LIBRARY)

IF (GDAL_FOUND)

   # show which CppUnit was found only if not quiet
   IF (NOT GDAL_FIND_QUIETLY)
      MESSAGE(STATUS "Found Gdal include directory : ${GDAL_INCLUDE_DIR}")
      MESSAGE(STATUS "Found Gdal library : ${GDAL_LIBRARY}")
   ENDIF (NOT GDAL_FIND_QUIETLY)

ELSE (GDAL_FOUND)

   # fatal error if CppUnit is required but not found
   IF (GDAL_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find Gdal. Make sure Gdal can be found in the default include path or in the environment variable GDAL_ROOT")
   ELSE (GDAL_FIND_REQUIRED)
     MESSAGE(STATUS "Could not find Gdal. Make sure Gdal can be found in the default include path or in the environment variable GDAL_ROOT")
   ENDIF (GDAL_FIND_REQUIRED)

ENDIF (GDAL_FOUND)
