include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/rtmidi
)

add_definitions(-fPIC)

set(midi_input_device_plugin_SRCS
    MIDIInputDevice.cpp
    MIDIMessage.cpp
)

automoc4_add_library(ketaroller_midi_input_device SHARED ${midi_input_device_plugin_SRCS})
target_link_libraries(ketaroller_midi_input_device ketaroller rtmidi ${QT_QTCORE_LIBRARY})

set(midi_output_port_plugin_SRCS
    MIDIOutputPort.cpp
    MIDIMessage.cpp
)

automoc4_add_library(ketaroller_midi_output_port SHARED ${midi_output_port_plugin_SRCS})
target_link_libraries(ketaroller_midi_output_port ketaroller rtmidi ${QT_QTCORE_LIBRARY})

install(TARGETS ketaroller_midi_input_device DESTINATION ${PLUGIN_INSTALL_DIR}/ketaroller)
install(TARGETS ketaroller_midi_output_port DESTINATION ${PLUGIN_INSTALL_DIR}/ketaroller)