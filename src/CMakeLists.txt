include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(ketarollerlib_SRCS
    AbstractDevice.cpp
    InputDevice.cpp
    Connection.cpp
    Port.cpp
    GesturedInputDevice.cpp
    GestureConnection.cpp
)

message("${QT_QTCORE_LIBRARY}")

automoc4_add_library(ketaroller SHARED ${ketarollerlib_SRCS})
target_link_libraries(ketaroller ${QT_QTCORE_LIBRARY})
