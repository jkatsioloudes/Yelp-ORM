cmake_minimum_required(VERSION 3.5)

add_custom_target(ODBHeaders odb --generate-schema --std c++14 --generate-query -d mssql ${Project_SOURCE_DIR}/Yelp.hpp SOURCES ${Project_SOURCE_DIR}/Yelp.hpp BYPRODUCTS ${PROJECT_BINARY_DIR}/Yelp-odb.cxx ${PROJECT_BINARY_DIR}/Yelp-odb.hxx)
add_executable(ADBCoursework1 ADBCoursework1.cpp ${PROJECT_BINARY_DIR}/Yelp-odb.cxx)
add_dependencies(ADBCoursework1 ODBHeaders)
set_property(TARGET ADBCoursework1 PROPERTY CXX_STANDARD 14)
target_include_directories(ADBCoursework1 PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(ADBCoursework1 PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(ADBCoursework1 odb odb-mssql)
