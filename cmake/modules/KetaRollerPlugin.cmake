function(add_ketaroller_plugin KCG_PLUGIN_TYPE KCG_INCLUDE_FILE KCG_CLASS KCG_SUBCLASS)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory.h

"#ifndef ${KCG_PLUGIN_TYPE}_PLUGIN_FACTORY_H
#define ${KCG_PLUGIN_TYPE}_PLUGIN_FACTORY_H

#include \"AbstractPluginFactory.h\"
#include \"${KCG_CLASS}.h\"
#include <QtPlugin>
#include \"${KCG_INCLUDE_FILE}\"

class Q_DECL_EXPORT ${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory : public KetaRoller::${KCG_CLASS}Factory
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::${KCG_CLASS}Factory)
    Q_DISABLE_COPY(${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory)
public:
    ${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory(QObject* parent = 0) : KetaRoller::${KCG_CLASS}Factory(parent) {}
    virtual ~${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory() {}
    virtual KetaRoller::${KCG_CLASS}* newInstance(QObject* parent) { return new ${KCG_SUBCLASS}(parent); }
};

#endif")

    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory.cpp
    "#include \"${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory.h\"
    Q_EXPORT_PLUGIN2(ketaroller_${KCG_PLUGIN_TYPE}_${KCG_CLASS}, ${KCG_PLUGIN_TYPE}${KCG_CLASS}Factory)
    ")
endfunction(add_ketaroller_plugin PLUGIN_TYPE INCLUDE_FILE CLASS SUBCLASS OUTFILE)