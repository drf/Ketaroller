/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include "PluginLoader.h"

#include "OutputPort.h"
#include "InputDevice.h"

#include "config-ketaroller.h"

#include <QCoreApplication>
#include <QPluginLoader>

#include <QDir>
#include <QHash>
#include <QDebug>

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
    QObject *loadPlugin(const QString &name);

    PluginLoader *q;

    QFileInfoList pluginList;
    QHash<QString, QPluginLoader*> cachedLoaders;
};

void PluginLoader::Private::refreshPluginList()
{
    QDir dir(PLUGIN_INSTALL_DIRECTORY);

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

QObject* PluginLoader::Private::loadPlugin(const QString& name)
{
    // Check if we have a cached loader first
    if (!cachedLoaders.contains(name)) {
        qDebug() << "Creating a new QPluginLoader";

        qDebug() << "Attempting to load " << name;

        foreach (const QFileInfo &info, pluginList) {
            if (info.baseName().contains(name)) {
                qDebug() << "Plugin found, attempting to load";

                QPluginLoader *loader = new QPluginLoader(info.absoluteFilePath(), q);

                cachedLoaders.insert(name, loader);
            }
        }

        if (!cachedLoaders.contains(name)) {
            qDebug() << "The requested plugin was not found";
            return 0;
        }
    }

    QPluginLoader *loader = cachedLoaders[name];

    QObject *plugin = loader->instance();

    if (!plugin) {
        qDebug() << "Failed to create a valid instance!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    qDebug() << "Plugin loaded successfully";

    return plugin;
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

InputDevice* PluginLoader::loadInputDevice(PluginLoader::Type type)
{
    QString pluginBaseName = QLatin1String("ketaroller_") + d->mapTypeToName(type) + QLatin1String("_input_device");

    QObject *plugin = d->loadPlugin(pluginBaseName);

    if (!plugin) {
        qDebug() << "Loading routine failed!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    InputDevice *device = qobject_cast< InputDevice* >(plugin);

    if (!device) {
        qDebug() << "Failed to cast to correct class type!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    return device;
}

OutputPort* PluginLoader::loadOutputPort(PluginLoader::Type type)
{
    QString pluginBaseName = QLatin1String("ketaroller_") + d->mapTypeToName(type) + QLatin1String("_output_port");

    QObject *plugin = d->loadPlugin(pluginBaseName);

    if (!plugin) {
        qDebug() << "Loading routine failed!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    OutputPort *port = qobject_cast< OutputPort* >(plugin);

    if (!port) {
        qDebug() << "Failed to cast to correct class type!! SHIVER IN AETERNAL DARKNESS";
        return 0;
    }

    return port;
}

}

#include "PluginLoader.moc"
