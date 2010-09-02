set(ketarollerlib_capitalized_HDRS
    AbstractDevice
    AbstractPluginFactory
    InputDevice
    InputPort
    OutputDevice
    OutputPort
    PluginLoader
    Port
)

install(FILES ${ketarollerlib_capitalized_HDRS} DESTINATION ${INCLUDE_INSTALL_DIR}/KetaRoller COMPONENT headers)
