include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(rtmidi_SRCS
    RtMidi.cpp
)

if (WIN32)
    find_library(WINMM_LIBRARY winmm)

    add_definitions(-D__WINDOWS_MM__)
elseif (APPLE)
    find_library(COREMIDI_LIBRARY CoreMidi)
    find_library(COREAUDIO_LIBRARY CoreAudio)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation )

    add_definitions(-D__MACOSX_CORE__)
else ()
    find_package(Alsa REQUIRED)
    find_package(PThread REQUIRED)

    include_directories(${ALSA_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})

    add_definitions(-D__LINUX_ALSASEQ__)
endif ()

add_library(rtmidi STATIC ${rtmidi_SRCS})

if (WIN32)
    target_link_libraries(rtmidi ${WINMM_LIBRARY})
elseif (APPLE)
    target_link_libraries(rtmidi ${COREMIDI_LIBRARY} ${COREFOUNDATION_LIBRARY} ${COREAUDIO_LIBRARY})
else ()
    target_link_libraries(rtmidi ${ALSA_LIBRARIES} ${PTHREAD_LIBRARIES})
endif ()

add_subdirectory(tests)
