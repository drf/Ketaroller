/*
    KetaRoller - an advanced signal router for musical devices

    Copyright (C) 2010 Dario Freddi <drf@kde.org>
    Copyright (C) 2010 Luca Mucci <luca.mucci@4cmp.it>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "PluginLoader.h"

#include "OutputPort.h"
#include "InputDevice.h"

#include <config-ketaroller.h>

#include <QCoreApplication>
#include <QPluginLoader>

#include <QDir>
#include <QHash>
#include <QDebug>
#include "OutputDevice.h"

namespace KetaRoller
{

class PluginLoaderHelper
{
public:
    PluginLoaderHelper() : q(0) {}
    ~PluginLoaderHelper() {
        delete q;
    }
    PluginLoader *q;
};

Q_GLOBAL_STATIC(PluginLoaderHelper, s_globalPluginLoader)

PluginLoader *PluginLoader::instance()
{
    if (!s_globalPluginLoader()->q) {
        new PluginLoader();
    }

    return s_globalPluginLoader()->q;
}

class PluginLoader::Private
{
public:
    Private(PluginLoader *qq)
        : q(qq)
    {
        refreshPluginList();
    }

    void refreshPluginList();
    QString mapTypeToName(Type type);
    AbstractPluginFactory *loadPlugin(const QString &name);

    PluginLoader *q;

    QFileInfoList pluginList;
    QHash<QString, AbstractPluginFactory*> cachedFactories;
};

void PluginLoader::Private::refreshPluginList()
{
    QDir dir = pluginPath();

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    pluginList = dir.entryInfoList();
}

QString PluginLoader::Private::mapTypeToName(PluginLoader::Type type)
{
    switch (type) {
        case MIDIType:
            return "midi";
        case TuioType:
            return "tuio";
        default:
            break;
    }

    return QString();
}

AbstractPluginFactory* PluginLoader::Private::loadPlugin(const QString& name)
{
    // Check if we have a cached loader first
    if (!cachedFactories.contains(name)) {
        qDebug() << "Creating a new QPluginLoader";

        qDebug() << "Attempting to load " << name;

        QPluginLoader *loader = 0;

        foreach (const QFileInfo &info, pluginList) {
            if (info.baseName().contains(name)) {
                qDebug() << "Plugin found, attempting to load" << info.baseName();

                loader = new QPluginLoader(info.absoluteFilePath(), q);
                break;
            }
        }

        if (!loader) {
            qDebug() << "The requested plugin was not found";
            return 0;
        }

        QObject *plugin = loader->instance();

        if (!plugin) {
            qDebug() << "Failed to create a valid instance!! SHIVER IN AETERNAL DARKNESS";
            qDebug() << loader->errorString();
            return 0;
        }

        qDebug() << "Plugin loaded successfully";

        AbstractPluginFactory *factory = qobject_cast< KetaRoller::AbstractPluginFactory* >(plugin);

        if (!factory) {
            qDebug() << "Failed to create a valid factory!! SHIVER IN AETERNAL DARKNESS";
            return 0;
        }

        cachedFactories.insert(name, factory);
    }

    return cachedFactories.value(name);
}

PluginLoader::PluginLoader(QObject* parent)
        : QObject(parent)
        , d(new Private(this))
{
    Q_ASSERT(!s_globalPluginLoader()->q);
    s_globalPluginLoader()->q = this;

    QCoreApplication::addLibraryPath(PLUGIN_INSTALL_DIRECTORY);
}

PluginLoader::~PluginLoader()
{
}

InputDevice* PluginLoader::loadInputDevice(PluginLoader::Type type, const QVariantMap &args)
{
    QString pluginBaseName = QLatin1String("ketaroller_") + d->mapTypeToName(type) + QLatin1String("_input_device");

    AbstractPluginFactory *factory = d->loadPlugin(pluginBaseName);

    if (!factory) {
        qDebug() << "Loading routine failed!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    InputDeviceFactory *inputFactory = qobject_cast< KetaRoller::InputDeviceFactory* >(factory);

    if (!inputFactory) {
        qDebug() << "Failed to cast to correct factory type!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    InputDevice *device = inputFactory->newInstance(this);

    device->init();

    return device;
}

OutputDevice* PluginLoader::loadOutputDevice(PluginLoader::Type type, const QVariantMap& args)
{
    QString pluginBaseName = QLatin1String("ketaroller_") + d->mapTypeToName(type) + QLatin1String("_output_device");

    AbstractPluginFactory *factory = d->loadPlugin(pluginBaseName);

    if (!factory) {
        qDebug() << "Loading routine failed!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    OutputDeviceFactory *outputFactory = qobject_cast< KetaRoller::OutputDeviceFactory* >(factory);

    if (!outputFactory) {
        qDebug() << "Failed to cast to correct factory type!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    OutputDevice *device = outputFactory->newInstance(this);

    device->init();

    return device;
}

OutputPort* PluginLoader::loadOutputPort(PluginLoader::Type type)
{
    QString pluginBaseName = QLatin1String("ketaroller_") + d->mapTypeToName(type) + QLatin1String("_output_port");

    AbstractPluginFactory *factory = d->loadPlugin(pluginBaseName);

    if (!factory) {
        qDebug() << "Loading routine failed!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    OutputPortFactory *outputPortFactory = qobject_cast< KetaRoller::OutputPortFactory* >(factory);

    if (!outputPortFactory) {
        qDebug() << "Failed to cast to correct factory type!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    OutputPort *port = outputPortFactory->newInstance(this);

    return port;
}

}

#include "PluginLoader.moc"
