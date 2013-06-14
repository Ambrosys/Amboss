
include_directories ( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )


add_executable ( KMLTests
  ColorTest.cpp
  ColorStyleTest.cpp
  IconStyleTest.cpp
  LineStyleTest.cpp
  PolyStyleTest.cpp
  LabelStyleTest.cpp
  StyleTest.cpp
  ElementWithNameTest.cpp
  ElementWithStyleUrlTest.cpp
  ElementWithStyleTest.cpp
  GeometryTest.cpp
  MultiGeometryTest.cpp
  PlacemarkTest.cpp
  FolderTest.cpp
  DocumentTest.cpp
  BoostGeometryTest.cpp )

target_link_libraries ( KMLTests gtest gtest_main )


# add_custom_command(TARGET KMLTests POST_BUILD COMMAND KMLTests )
add_test( NAME KMLTests COMMAND KMLTests )