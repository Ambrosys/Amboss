#
# - Find Sqlite3
# This module finds an installed Sqlite3 package, if the package is not available it
# configures the version in thrirdparty/sqlite3.
#
# It sets the following variables:
#  SQLITE3_FOUND       - Set to false, or undefined, if CppUnit isn't found.
#  SQLITE3_INCLUDE_DIR - The CppUnit include directory.
#  SQLITE3_LIBRARY     - The CppUnit library to link against.

SET(SQLITE3_ROOT $ENV{SQLITE3_ROOT})


FIND_PATH(SQLITE3_INCLUDE_DIR sqlite3.h ${SQLITE3_ROOT} )
FIND_LIBRARY(SQLITE3_LIBRARY NAMES sqlite3 ${SQLITE3_ROOT} )


IF (SQLITE3_INCLUDE_DIR AND SQLITE3_LIBRARY)
  SET(SQLITE3_FOUND TRUE)
ENDIF (SQLITE3_INCLUDE_DIR AND SQLITE3_LIBRARY)


IF ( SQLITE3_FOUND)

  # show which Sqlite was found only if not quiet
  IF (NOT Sqlite3_FIND_QUIETLY)
    MESSAGE(STATUS "Found Sqlite3: ${SQLITE3_LIBRARY}")
  ENDIF (NOT Sqlite3_FIND_QUIETLY)

ELSE ( SQLITE3_FOUND)

  MESSAGE(STATUS "No installation of Sqlite3 found. Try to create a default version in ${SQLITE_DEFAULT_DIR}!"  )


  # try to build sqlite from the default directory
  IF (IS_DIRECTORY ${SQLITE_DEFAULT_DIR} )

    ADD_SUBDIRECTORY( ${SQLITE_DEFAULT_DIR} )
    SET(SQLITE3_INCLUDE_DIR ${SQLITE_DEFAULT_DIR})
    SET(SQLITE3_LIBRARY sqlite3 )
     
  ELSE (IS_DIRECTORY ${SQLITE_DEFAULT_DIR} )

    # fatal error if CppUnit is required but not found
    IF (Sqlite3_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find Sqlite3")
    ENDIF (Sqlite3_FIND_REQUIRED)

  ENDIF (IS_DIRECTORY ${SQLITE_DEFAULT_DIR} )

ENDIF (SQLITE3_FOUND)