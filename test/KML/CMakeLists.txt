
include_directories ( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )


add_executable ( TestMain
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
  PlacemarkTest.cpp
  FolderTest.cpp
  DocumentTest.cpp
  BoostGeometryTest.cpp )

target_link_libraries ( TestMain gtest gtest_main )


add_custom_command(TARGET TestMain POST_BUILD COMMAND TestMain)
