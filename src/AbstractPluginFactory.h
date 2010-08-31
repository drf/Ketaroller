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

#ifndef ABSTRACTPLUGINFACTORY_H
#define ABSTRACTPLUGINFACTORY_H

#include <QtCore/QObject>

namespace KetaRoller {

/**
 * @brief Abstract factory for creating InputDevices
 *
 * This class serves as an helper for creating instances of a plugin.
 * It's an internal class and should not be reimplemented directly - please
 * read @ref create_plugins_cmake_sec "CMake's documentation on creating plugins"
 * to learn how to autogenerate plugins.
 * <br><br>
 * Please read @ref plugin_factory_model_sec "the plugin factory model" if you're interested in knowing
 * how PluginFactories work.
 */
class AbstractPluginFactory : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractPluginFactory)
public:
    AbstractPluginFactory(QObject* parent = 0);
    virtual ~AbstractPluginFactory();
};

}

#endif // ABSTRACTPLUGINFACTORY_H
