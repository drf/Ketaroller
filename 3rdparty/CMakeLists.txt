include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/oscpack
)

add_definitions(-fPIC)

if (WIN32)
    find_library(WINMM_LIBRARY winmm)
    find_library(WS2_32_LIBRARY ws2_32)

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

add_subdirectory(oscpack)
add_subdirectory(tuio)
add_subdirectory(rtmidi)
