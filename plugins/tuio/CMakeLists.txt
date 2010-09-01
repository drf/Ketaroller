include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack
    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack/ip
)


### TUIO Input Device

add_ketaroller_plugin("TUIO" "TuioInputDevice.h" "InputDevice" "TuioInputDevice")
set(tuio_input_device_plugin_SRCS
    TuioInputDevice.cpp
    FiducialObject.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/TUIOInputDeviceFactory.cpp
)

qt4_automoc(${tuio_input_device_plugin_SRCS})

add_library(ketaroller_tuio_input_device SHARED ${tuio_input_device_plugin_SRCS})
target_link_libraries(ketaroller_tuio_input_device ketaroller tuio ${QT_QTGUI_LIBRARY})

if (WIN32)
    install(TARGETS ketaroller_tuio_input_device RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT tuioplugins)
else (WIN32)
    install(TARGETS ketaroller_tuio_input_device LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT tuioplugins)
endif (WIN32)


### TUIO Output Port

add_ketaroller_plugin("TUIO" "TuioOutputPort.h" "OutputPort" "TuioOutputPort")
set(tuio_output_port_plugin_SRCS
    TuioOutputPort.cpp
    FiducialObject.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/TUIOOutputPortFactory.cpp
)

qt4_automoc(${tuio_output_port_plugin_SRCS})

add_library(ketaroller_tuio_output_port SHARED ${tuio_output_port_plugin_SRCS})
target_link_libraries(ketaroller_tuio_output_port ketaroller tuio ${QT_QTGUI_LIBRARY})

if (WIN32)
    install(TARGETS ketaroller_tuio_output_port RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT tuioplugins)
else (WIN32)
    install(TARGETS ketaroller_tuio_output_port LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT tuioplugins)
endif (WIN32)
