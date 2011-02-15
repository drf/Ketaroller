include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/bct
    ${CMAKE_SOURCE_DIR}/plugins
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
)

set(bct_controller_SRCS
    main.cpp
    MainWindow.cpp
    MIDIWidget.cpp
    FiducialWidget.cpp
)

set(bct_controller_UIS
    window1.ui
    midiWidget.ui
    fiducialWidget.ui
)

qt4_wrap_ui(bct_controller_UIS_H ${bct_controller_UIS})
qt4_automoc(${bct_controller_SRCS})

add_executable(bctcontroller ${bct_controller_SRCS} ${bct_controller_UIS_H})
target_link_libraries(bctcontroller ketaroller ketaroller_bct_output_device ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})

install(TARGETS bctcontroller RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT bctplugins)
