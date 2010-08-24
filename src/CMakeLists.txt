include_directories(${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-ketaroller.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/config-ketaroller.h
               @ONLY)

set(ketarollerlib_SRCS
    AbstractDevice.cpp
    InputDevice.cpp
    Port.cpp
    InputPort.cpp
    OutputPort.cpp
    GesturedInputDevice.cpp
    PluginLoader.cpp
)

automoc4_add_library(ketaroller SHARED ${ketarollerlib_SRCS})
target_link_libraries(ketaroller ${QT_QTCORE_LIBRARY})
