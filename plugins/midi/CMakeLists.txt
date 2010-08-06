include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/rtmidi
)

set(midi_input_device_plugin_SRCS
    MIDIInputDevice.cpp
    MIDIMessage.cpp
)

automoc4_add_library(ketaroller_midi_input_device SHARED ${midi_input_device_plugin_SRCS})
target_link_libraries(ketaroller_midi_input_device ketaroller rtmidi ${QT_QTGUI_LIBRARY})
