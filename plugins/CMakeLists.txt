
include(KetaRollerPlugin)

if (QT_QTGUI_FOUND)
    add_subdirectory(tuio)
endif (QT_QTGUI_FOUND)

add_subdirectory(midi)
