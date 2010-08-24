include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack
    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack/ip
)

set(tuio_input_device_plugin_SRCS
    TuioInputDevice.cpp
    FiducialObject.cpp
)

automoc4_add_library(ketaroller_tuio_input_device SHARED ${tuio_input_device_plugin_SRCS})
target_link_libraries(ketaroller_tuio_input_device ketaroller tuio ${QT_QTGUI_LIBRARY})

set(tuio_output_port_plugin_SRCS
    TuioOutputPort.cpp
    FiducialObject.cpp
)

automoc4_add_library(ketaroller_tuio_output_port SHARED ${tuio_output_port_plugin_SRCS})
target_link_libraries(ketaroller_tuio_output_port ketaroller tuio ${QT_QTGUI_LIBRARY})

install(TARGETS ketaroller_tuio_input_device DESTINATION ${PLUGIN_INSTALL_DIR}/ketaroller)
install(TARGETS ketaroller_tuio_output_port DESTINATION ${PLUGIN_INSTALL_DIR}/ketaroller)
