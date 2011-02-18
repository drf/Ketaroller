cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(ketaroller)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

find_package(Qt4 COMPONENTS QtCore REQUIRED)
include(${QT_USE_FILE})

set(PROJECT_VERSION "0.1.0")

include(InstallSettings)
include(UseDoxygen)
include(MacroLogFeature)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDES}
    ${CMAKE_SOURCE_DIR}/src
)

macro_log_feature(QT_QTTEST_FOUND "Qt4 QtTest Library"
                  "A library for creating test cases, part of the Qt framework"
                  "http://qt.nokia.com/" FALSE ""
                  "Needed to build test cases and examples")
macro_log_feature(QT_QTGUI_FOUND "Qt4 QtGui Library"
                  "A GUI library, part of the Qt framework"
                  "http://qt.nokia.com/" FALSE ""
                  "Needed to build TUIO plugins")

add_subdirectory(src)
add_subdirectory(plugins)
add_subdirectory(3rdparty)
add_subdirectory(gui)
add_subdirectory(tuioredirector)

if (QT_QTTEST_FOUND)
    add_subdirectory(tests)
endif (QT_QTTEST_FOUND)

add_subdirectory(examples)

add_custom_target(uninstall
        COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

include(KetaRollerCPack)

macro_display_feature_log()
