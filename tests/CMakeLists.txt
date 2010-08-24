enable_testing()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

automoc4_add_executable(plugin-load-test
    testpluginload.cpp
)

target_link_libraries(plugin-load-test
    ${QT_QTCORE_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
)

automoc4_add_executable(midi-ports-test
    testmidiports.cpp
    ../plugins/midi/MIDIOutputPort.cpp
    ../plugins/midi/MIDIMessage.cpp
)

target_link_libraries(midi-ports-test
    ${QT_QTCORE_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
)

add_test(PluginLoaderMIDITest ${CMAKE_CURRENT_BINARY_DIR}/plugin-load-test)
add_test(MIDICommunicationTest ${CMAKE_CURRENT_BINARY_DIR}/midi-ports-test)
