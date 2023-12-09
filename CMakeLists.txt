cmake_minimum_required(VERSION 3.24)
project(PrimarySoftware)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(./googletest)
include_directories(${PROJECT_SOURCE_DIR}/src/include ./googletest/include/gtest)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/googletest)
target_link_libraries(${PROJECT_NAME} gtest)
add_executable(PrimarySoftware main.cpp dialog.cpp)
