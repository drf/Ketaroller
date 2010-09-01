include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/rtmidi
)

include(KetaRollerPlugin)

add_definitions(-fPIC)

add_ketaroller_plugin("MIDI" "MIDIInputDevice.h" "InputDevice" "MIDIInputDevice")
set(midi_input_device_plugin_SRCS
    MIDIInputDevice.cpp
    MIDIMessage.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/MIDIInputDeviceFactory.cpp
)

qt4_automoc(${midi_input_device_plugin_SRCS})

add_library(ketaroller_midi_input_device SHARED ${midi_input_device_plugin_SRCS})
target_link_libraries(ketaroller_midi_input_device ketaroller rtmidi ${QT_QTCORE_LIBRARY})

add_ketaroller_plugin("MIDI" "MIDIOutputPort.h" "OutputPort" "MIDIOutputPort")
set(midi_output_port_plugin_SRCS
    MIDIOutputPort.cpp
    MIDIMessage.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/MIDIOutputPortFactory.cpp
)

qt4_automoc(${midi_output_port_plugin_SRCS})

add_library(ketaroller_midi_output_port SHARED ${midi_output_port_plugin_SRCS})
target_link_libraries(ketaroller_midi_output_port ketaroller rtmidi ${QT_QTCORE_LIBRARY})

install(TARGETS ketaroller_midi_input_device DESTINATION ${PLUGIN_INSTALL_DIR}/ketaroller)
install(TARGETS ketaroller_midi_output_port DESTINATION ${PLUGIN_INSTALL_DIR}/ketaroller)