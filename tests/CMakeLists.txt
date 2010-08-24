enable_testing()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
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

automoc4_add_executable(tuio-ports-test
    testtuioports.cpp
    ../plugins/tuio/TuioOutputPort.cpp
    ../plugins/tuio/FiducialObject.cpp
)

target_link_libraries(tuio-ports-test
    ${QT_QTCORE_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
    tuio
)

add_test(PluginLoaderMIDITest ${CMAKE_CURRENT_BINARY_DIR}/plugin-load-test)
add_test(MIDICommunicationTest ${CMAKE_CURRENT_BINARY_DIR}/midi-ports-test)
add_test(TuioCommunicationTest ${CMAKE_CURRENT_BINARY_DIR}/tuio-ports-test)
