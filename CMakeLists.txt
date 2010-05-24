project(ketaroller)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(Qt4 REQUIRED)
find_package(Automoc4 REQUIRED)

add_subdirectory(src)
add_subdirectory(plugins)
add_subdirectory(3rdparty)
