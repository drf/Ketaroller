include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack
    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack/ip
)

set(tuio_plugin_SRCS
    TuioInputDevice.cpp
    FiducialObject.cpp
)

automoc4_add_library(ketaroller_tuio SHARED ${tuio_plugin_SRCS})
target_link_libraries(ketaroller_tuio ketaroller tuio)