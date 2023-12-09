cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

project(demo)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp dialog.cpp)

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
