include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(KetaRollerPlugin)

if (QT_QTGUI_FOUND)
    add_subdirectory(tuio)
endif (QT_QTGUI_FOUND)

add_subdirectory(midi)

add_subdirectory(bct)