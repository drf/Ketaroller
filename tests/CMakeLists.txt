enable_testing()

add_definitions(-DINTO_TESTING)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
)

### Plugin load test

set(plugin_load_test_SRCS
    testpluginload.cpp
)

qt4_automoc(${plugin_load_test_SRCS})

add_executable(plugin-load-test ${plugin_load_test_SRCS})

target_link_libraries(plugin-load-test
    ${QT_QTCORE_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
)

install(TARGETS plugin-load-test RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT tests)


### MIDI ports test

set(midi_ports_test_SRCS
    testmidiports.cpp
    ../plugins/midi/MIDIOutputPort.cpp
    ../plugins/midi/MIDIMessage.cpp
)

qt4_automoc(${midi_ports_test_SRCS})

add_executable(midi-ports-test ${midi_ports_test_SRCS})

target_link_libraries(midi-ports-test
    ${QT_QTCORE_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
)

install(TARGETS midi-ports-test RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT tests)


### TUIO ports test

set(tuio_ports_test_SRCS
    testtuioports.cpp
    ../plugins/tuio/TuioOutputPort.cpp
    ../plugins/tuio/FiducialObject.cpp
)

qt4_automoc(${tuio_ports_test_SRCS})

add_executable(tuio-ports-test ${tuio_ports_test_SRCS})

target_link_libraries(tuio-ports-test
    ${QT_QTCORE_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
    tuio
)

install(TARGETS tuio-ports-test RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT tests)

### CTest targets

add_test(PluginLoaderMIDITest ${CMAKE_CURRENT_BINARY_DIR}/plugin-load-test)
add_test(MIDICommunicationTest ${CMAKE_CURRENT_BINARY_DIR}/midi-ports-test)
add_test(TuioCommunicationTest ${CMAKE_CURRENT_BINARY_DIR}/tuio-ports-test)

add_subdirectory(manual)
