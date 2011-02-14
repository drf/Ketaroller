include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3rdparty/tuio
    ${CMAKE_SOURCE_DIR}/src
)

### BCT Output Device

add_ketaroller_plugin("BCT" "BctOutputDevice.h" "OutputDevice" "BctOutputDevice")
set(bct_output_device_plugin_SRCS
    BctOutputDevice.cpp
    bctnetworkprotocol.cpp
    ../tuio/FiducialObject.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/BCTOutputDeviceFactory.cpp
)

qt4_automoc(${bct_output_device_plugin_SRCS})

add_library(ketaroller_bct_output_device SHARED ${bct_output_device_plugin_SRCS})
target_link_libraries(ketaroller_bct_output_device ketaroller tuio ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})

if (WIN32)
    install(TARGETS ketaroller_bct_output_device RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT bctplugins)
else (WIN32)
    install(TARGETS ketaroller_bct_output_device LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT bctplugins)
endif (WIN32)
