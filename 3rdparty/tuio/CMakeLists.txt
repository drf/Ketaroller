include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(tuio_SRCS
    TuioClient.cpp
    TuioServer.cpp
    TuioTime.cpp
)

add_library(tuio STATIC ${tuio_SRCS})
target_link_libraries(tuio oscpack)

if (WIN32)
    target_link_libraries(tuio ${WINMM_LIBRARY} ${WS2_32_LIBRARY})
endif (WIN32)
