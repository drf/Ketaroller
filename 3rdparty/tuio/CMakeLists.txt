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
