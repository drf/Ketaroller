include_directories(${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-ketaroller.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/config-ketaroller.h
               @ONLY)

set(ketarollerlib_SRCS
    AbstractDevice.cpp
    AbstractPluginFactory.cpp
    InputDevice.cpp
    Port.cpp
    InputPort.cpp
    OutputPort.cpp
    OutputDevice.cpp
    #GesturedInputDevice.cpp
    PluginLoader.cpp

    config-ketaroller.cpp
)

qt4_automoc(${ketarollerlib_SRCS})

add_library(ketaroller SHARED ${ketarollerlib_SRCS})
target_link_libraries(ketaroller ${QT_QTCORE_LIBRARY})
