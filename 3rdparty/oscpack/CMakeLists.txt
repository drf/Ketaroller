include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/ip
    ${CMAKE_CURRENT_SOURCE_DIR}/osc
)

if (WIN32)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ip/win32)
else (WIN32)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ip/posix)
endif (WIN32)

# Use little endianess
add_definitions(-DOSC_HOST_LITTLE_ENDIAN)

set(oscpack_SRCS
    ip/IpEndpointName.cpp

    osc/OscOutboundPacketStream.cpp
    osc/OscPrintReceivedElements.cpp
    osc/OscReceivedElements.cpp
    osc/OscTypes.cpp
)

if (WIN32)
    set(oscpack_SRCS
        ${oscpack_SRCS}
        ip/win32/NetworkingUtils.cpp
        ip/win32/UdpSocket.cpp
    )
else (WIN32)
    set(oscpack_SRCS
        ${oscpack_SRCS}
        ip/posix/NetworkingUtils.cpp
        ip/posix/UdpSocket.cpp
    )
endif (WIN32)

add_library(oscpack STATIC ${oscpack_SRCS})
