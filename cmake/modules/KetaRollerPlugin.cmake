function(add_ketaroller_plugin PLUGIN_TYPE INCLUDE_FILE CLASS SUBCLASS)
    set(KCG_PLUGIN_TYPE ${PLUGIN_TYPE})
    set(KCG_INCLUDE_FILE ${INCLUDE_FILE})
    set(KCG_CLASS ${CLASS})
    set(KCG_SUBCLASS ${SUBCLASS})

    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/pluginfactory.h.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory.h @ONLY)

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory.cpp
    "#include \"${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory.h\"
    Q_EXPORT_PLUGIN2(ketaroller_${KCG_PLUGIN_TYPE}_${KCG_CLASS}, ${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory)
    ")
endfunction(add_ketaroller_plugin PLUGIN_TYPE INCLUDE_FILE CLASS SUBCLASS OUTFILE)