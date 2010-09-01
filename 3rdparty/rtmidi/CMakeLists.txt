include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(rtmidi_SRCS
    RtMidi.cpp
)

add_library(rtmidi STATIC ${rtmidi_SRCS})

if (WIN32)
    target_link_libraries(rtmidi ${WINMM_LIBRARY} ${WS2_32_LIBRARY})
elseif (APPLE)
    target_link_libraries(rtmidi ${COREMIDI_LIBRARY} ${COREFOUNDATION_LIBRARY} ${COREAUDIO_LIBRARY})
else ()
    target_link_libraries(rtmidi ${ALSA_LIBRARIES} ${PTHREAD_LIBRARIES})
endif ()

add_subdirectory(tests)
