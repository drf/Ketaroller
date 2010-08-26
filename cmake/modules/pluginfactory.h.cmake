#ifndef @KCG_PLUGIN_TYPE@_PLUGIN_FACTORY_H
#define @KCG_PLUGIN_TYPE@_PLUGIN_FACTORY_H

#include "AbstractPluginFactory.h"
#include "@KCG_CLASS@.h"
#include <QtPlugin>
#include "@KCG_INCLUDE_FILE@"

class Q_DECL_EXPORT @KCG_PLUGIN_TYPE@@KCG_CLASS@Factory : public KetaRoller::@KCG_CLASS@Factory
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::@KCG_CLASS@Factory)
    Q_DISABLE_COPY(@KCG_PLUGIN_TYPE@@KCG_CLASS@Factory)
public:
    @KCG_PLUGIN_TYPE@@KCG_CLASS@Factory(QObject* parent = 0) : KetaRoller::@KCG_CLASS@Factory(parent) {}
    virtual ~@KCG_PLUGIN_TYPE@@KCG_CLASS@Factory() {}
    virtual KetaRoller::@KCG_CLASS@* newInstance(QObject* parent) { return new @KCG_SUBCLASS@(parent); }
};

#endif
