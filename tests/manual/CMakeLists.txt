include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
    ${CMAKE_SOURCE_DIR}/3rdparty/rtmidi

)

function(add_ketaroller_manual_test _NAME)
    ketaroller_extract_libraries(_srcs _libs ${ARGN})

    set(_target_SRCS
        ${_NAME}.cpp
        ${_srcs}
    )

    qt4_automoc(${_target_SRCS})

    add_executable(${_NAME} ${_target_SRCS})

    target_link_libraries(${_NAME}
        ${QT_QTCORE_LIBRARY}
        ${QT_QTTEST_LIBRARY}
        ketaroller
        ${_libs}
    )

    install(TARGETS ${_NAME} RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT tests)
endfunction(add_ketaroller_manual_test _NAME)

add_ketaroller_manual_test(tuioreactivisionmanualtest
                           tuioreactivisionmanualtest.cpp
                           ../../plugins/tuio/FiducialObject.cpp
                           LIBRARIES tuio)
add_ketaroller_manual_test(tuioportstofiducialstest
                           ../../plugins/tuio/FiducialObject.cpp
                           LIBRARIES tuio)

add_ketaroller_manual_test(midimanualtest
                           ../../plugins/midi/MIDIMessage.cpp
                           LIBRARIES rtmidi)
