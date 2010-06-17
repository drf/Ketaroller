include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(rtmidi_SRCS
	RtMidi.cpp
)

add_library(rtmidi STATIC ${rtmidi_SRCS})
