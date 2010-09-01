include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
)

### Reactivision test

set(tuio_reactivision_manual_test_SRCS
    tuioreactivisionmanualtest.cpp
    ../../plugins/tuio/FiducialObject.cpp
)

qt4_automoc(${tuio_reactivision_manual_test_SRCS})

add_executable(tuio-reactivision-manual-test ${tuio_reactivision_manual_test_SRCS})

target_link_libraries(tuio-reactivision-manual-test
    ${QT_QTGUI_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
    tuio
)

install(TARGETS tuio-reactivision-manual-test RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT tests)


### Ports to fiducial test

set(tuio_ports_to_fiducial_test_SRCS
    tuioportstofiducialstest.cpp
    ../../plugins/tuio/FiducialObject.cpp
)


qt4_automoc(${tuio_ports_to_fiducial_test_SRCS})

add_executable(tuio-ports-to-fiducial-test ${tuio_ports_to_fiducial_test_SRCS})

target_link_libraries(tuio-ports-to-fiducial-test
    ${QT_QTGUI_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
    tuio
)

install(TARGETS tuio-ports-to-fiducial-test RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT tests)
