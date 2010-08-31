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

#ifndef ABSTRACTDEVICE_H
#define ABSTRACTDEVICE_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

struct QUuid;

namespace KetaRoller {

class AbstractDevicePrivate;
/**
 * @brief Base class for all kinds of devices
 *
 * This class represents an Abstract Device with no logic except initialization.
 *
 * @b NEVER subclass this class directly: subclass InputDevice or OutputDevice instead.
 *
 * @sa InputDevice
 * @sa OutputDevice
 */
class Q_DECL_EXPORT AbstractDevice : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractDevice)
    Q_DISABLE_COPY(AbstractDevice)
public:
    /**
     * Base destructor
     */
    virtual ~AbstractDevice();

    /**
     * @returns An unique ID associated with this device
     */
    QUuid uuid() const;

protected:
    /**
     * Base constructor
     */
    AbstractDevice(AbstractDevicePrivate &dd, QObject* parent = 0);

    /**
     * @brief Initializes the device.
     *
     * This function is never meant to be called directly: \c PluginLoader will take care of that for you.
     * However, this function \b CAN be reimplemented in plugins implementing an AbstractDevice such as InputDevice
     * or OutputDevice.
     *
     * You should avoid putting anything in your plugin's constructor and instead save it for this function
     * to let the initialization happen safely. It is \b REQUIRED that when this function has returned, the InputDevice
     * is ready to be used.
     *
     * You probably want to initialize your framework in this function - have a look at TUIO's implementation for
     * an overview of what you should do here.
     *
     * @param args A set of arbitrary arguments which might be required by the plugin to be initialized. Please see
     *             @ref plugins_init_arguments_sec "Plugin arguments" for learning more on this.
     */
    virtual void init(const QVariantMap &args = QVariantMap());

    AbstractDevicePrivate * const d_ptr;
};

}

#endif // ABSTRACTDEVICE_H
