include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
)

set(tuiogestureexample_SRCS
    tuiogestureexample.cpp
)

qt4_automoc(${tuiogestureexample_SRCS})

add_executable(tuiogestureexample ${tuiogestureexample_SRCS})

target_link_libraries(tuiogestureexample
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ketaroller
)

install(TARGETS tuiogestureexample RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT tests)
