include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(ketarollerlib_SRCS
    InputDevice.cpp
    BaseSignal.cpp)

automoc4_add_library(ketaroller SHARED ${ketarollerlib_SRCS})
target_link_libraries(ketaroller ${QT4_QTCORE_LIBRARY})
