include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
)

automoc4_add_executable(tuio-reactivision-manual-test
    tuioreactivisionmanualtest.cpp
    ../../plugins/tuio/FiducialObject.cpp
)

target_link_libraries(tuio-reactivision-manual-test
    ${QT_QTGUI_LIBRARY}
    ${QT_QTTEST_LIBRARY}
    ketaroller
    tuio
)