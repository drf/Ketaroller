project(ketaroller)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(Qt4 REQUIRED)
find_package(Automoc4 REQUIRED)

set(PROJECT_VERSION "0.1.0")

include(InstallSettings)
include(UseDoxygen)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(src)
add_subdirectory(plugins)
add_subdirectory(3rdparty)
add_subdirectory(tests)

add_custom_target(uninstall
        COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
