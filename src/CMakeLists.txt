set(ketarollerlib_SRCS
    InputDevice.cpp)

add_library(ketaroller SHARED ${ketarollerlib_SRCS})
target_link_libraries(ketaroller ${QT4_QTCORE_LIBRARY})
