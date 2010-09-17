enable_testing()

add_definitions(-DINTO_TESTING)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
)

MACRO (KETAROLLER_EXTRACT_LIBRARIES _ketaroller_files _ketaroller_libraries)
  SET(${_ketaroller_files})
  SET(${_ketaroller_libraries})
  SET(_KETAROLLER_DOING_LIBRARIES FALSE)
  FOREACH(_currentArg ${ARGN})
    IF ("${_currentArg}" STREQUAL "LIBRARIES")
      SET(_KETAROLLER_DOING_LIBRARIES TRUE)
    ELSE ("${_currentArg}" STREQUAL "LIBRARIES")
      IF(_KETAROLLER_DOING_LIBRARIES)
        LIST(APPEND ${_ketaroller_libraries} "${_currentArg}")
      ELSE(_KETAROLLER_DOING_LIBRARIES)
        LIST(APPEND ${_ketaroller_files} "${_currentArg}")
      ENDIF(_KETAROLLER_DOING_LIBRARIES)
    ENDIF ("${_currentArg}" STREQUAL "LIBRARIES")
  ENDFOREACH(_currentArg)
ENDMACRO (KETAROLLER_EXTRACT_LIBRARIES)

function(add_ketaroller_test _NAME _PRETTY_NAME)
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

    add_test(${_PRETTY_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${_NAME})
endfunction(add_ketaroller_test _NAME _PRETTY_NAME)

### Plugin load test

add_ketaroller_test(testpluginload PluginLoaderMIDITest)
add_ketaroller_test(testmidiports MIDICommunicationTest
                    ../plugins/midi/MIDIOutputPort.cpp
                    ../plugins/midi/MIDIMessage.cpp)
add_ketaroller_test(testtuioports TuioCommunicationTest
                    ../plugins/tuio/TuioOutputPort.cpp
                    ../plugins/tuio/FiducialObject.cpp
                    LIBRARIES tuio)

add_subdirectory(manual)
