include_directories(${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-ketaroller.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/config-ketaroller.h
               @ONLY)

add_definitions(-DBUILD_KETAROLLER_LIB)

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

set(ketarollerlib_HDRS
    AbstractDevice.h
    AbstractPluginFactory.h
    InputDevice.h
    Port.h
    InputPort.h
    OutputPort.h
    OutputDevice.h
    PluginLoader.h

    ketaroller-export.h
)

qt4_automoc(${ketarollerlib_SRCS})

add_library(ketaroller SHARED ${ketarollerlib_SRCS})
target_link_libraries(ketaroller ${QT_QTCORE_LIBRARY})

if (WIN32)
    install(TARGETS ketaroller RUNTIME DESTINATION ${LIB_INSTALL_DIR} COMPONENT mainlibrary
                               ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT headers)
else (WIN32)
    install(TARGETS ketaroller LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT mainlibrary
                               ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT headers)
endif (WIN32)

install(FILES ${ketarollerlib_HDRS} DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT headers)
