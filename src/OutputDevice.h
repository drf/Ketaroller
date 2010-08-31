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

#ifndef KETAROLLER_OUTPUTDEVICE_H
#define KETAROLLER_OUTPUTDEVICE_H

#include <AbstractDevice.h>
#include "AbstractPluginFactory.h"

#include <QVariantMap>

namespace KetaRoller {

class OutputPort;

class OutputDevicePrivate;
/**
 * @brief Base class for Output Devices
 *
 * This class serves as an interface for implementing an Output Device. This device is meant
 * to receive messages coming from one or more OutputPorts and process them.
 * <br><br>
 * When reimplementing this class in your plugin, you will need to add one method as a private slot, newDataFromPort.
 * This is explained in @ref creating_output_device_plugin_sec "creating an OutputDevice".
 *
 * @section handle_ports_output_device_sec Handling ports
 *
 * The whole logic for handling ports is contained into the base OutputDevice class, however,
 * you will have to reimplement validatePort to actually determine if your device supports
 * a specific port. For example, in that function you can check if the port type is supported,
 * if some compulsory parameters are present, etc.
 *
 * Still, consider that the I/O logic still happens in OutputPort.
 */
class Q_DECL_EXPORT OutputDevice : public KetaRoller::AbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(OutputDevice)
    Q_DISABLE_COPY(OutputDevice)

    friend class PluginLoader;

public:
    /**
     * Base destructor
     */
    virtual ~OutputDevice();

    /**
     * @returns The OutputPorts connected to this device
     */
    QList< OutputPort* > outputPorts() const;

    /**
     * Attempts to add an incoming port to this device. The port will be validated.
     *
     * @param port a valid OutputPort to be added to this device.
     *
     * @returns \c true if the port has been successfully added, \c false if the device rejected
     *          the port for any reason.
     */
    bool addIncomingPort(OutputPort *port);

    /**
     * Removes an existing port from this device.
     *
     * @param port An existing port of this device to be removed
     *
     * @sa removeAllIncomingPorts
     */
    void removeIncomingPort(OutputPort *port);

    /**
     * Removes all existing ports from this device.
     *
     * @sa removeIncomingPort
     */
    void removeAllIncomingPorts();

protected:
    /**
     * Creates a new InputDevice.
     *
     * You cannot use this constructor directly, instead, if you want to create a new OutputDevice,
     * please use PluginLoader's methods for loading specific OutputDevices.
     *
     * @sa KetaRoller::PluginLoader
     */
    OutputDevice(QObject *parent = 0);

    /**
     * @brief Validates a port
     *
     * This function is never meant to be called directly: \c addIncomingPort will take care of that for you.
     * However, this function \b MUST be reimplemented in plugins implementing an OutputDevice.
     *
     * This function will be called whenever a port is being added - depending on the return value, the port
     * will be added to the device or not. Please return \c true if the port is valid and can be added to the device,
     * or \c false if not.
     *
     * This function <b>MUST NOT</b> alter any value inside \c port : it should be completely transparent and ac
     * as a verifier only.
     *
     * @param port The port which should be validated
     *
     * @returns \c true if the port is valid and can be added to the device, \c false otherwise.
     */
    virtual bool validatePort(KetaRoller::OutputPort *port) = 0;

Q_SIGNALS:
    /**
     * This signal will be emitted whenever a port is added to the device
     *
     * @param port The port which has just been added
     *
     * @note Please note that this signal will be emitted only if addIncomingPort was successful.
     */
    void portAdded(KetaRoller::OutputPort *port);
    /**
     * This signal will be emitted whenever a port is removed from the device
     *
     * @param port The port which has just been removed
     *
     * @note Please note that if the port was deleted due to a cascade effect while disconnecting an InputPort
     *       or an InputDevice, this signal will be emitted \c BEFORE any action eventually specified through
     *       \c PortRemovalModes will take place: however, it is not guaranteed that on the next event loop
     *       run the port will still be a valid object.
     */
    void portRemoved(KetaRoller::OutputPort *port);
};

/**
 * @brief Factory for creating OutputDevices
 *
 * This class serves as an helper for creating instances of a plugin.
 * It's an internal class and should not be reimplemented directly - please
 * read @ref create_plugins_cmake_sec "CMake's documentation on creating plugins"
 * to learn how to autogenerate plugins.
 * <br><br>
 * Please read @ref plugin_factory_model_sec "the plugin factory model" if you're interested in knowing
 * how PluginFactories work.
 */
class Q_DECL_EXPORT OutputDeviceFactory : public AbstractPluginFactory
{
    Q_OBJECT
public:
    OutputDeviceFactory(QObject* parent = 0);
    virtual ~OutputDeviceFactory();

    virtual OutputDevice *newInstance(QObject *parent) = 0;
};

}

Q_DECLARE_INTERFACE(KetaRoller::OutputDevice, "org.ketamina.OutputDevice/0.1")
Q_DECLARE_INTERFACE(KetaRoller::OutputDeviceFactory, "org.ketamina.OutputDeviceFactory/0.1")

#define KETAROLLER_OUTPUT_DEVICE_PLUGIN_FACTORY(type, _gen) class Q_DECL_EXPORT _gen##Factory : public KetaRoller::OutputDeviceFactory \
{ \
    Q_OBJECT \
    Q_INTERFACES(KetaRoller::OutputDeviceFactory) \
    Q_DISABLE_COPY(_gen) \
public: \
    _genFactory(QObject* parent = 0) : KetaRoller::OutputDeviceFactory(parent) {} \
    virtual ~_gen##Factory() {} \
    virtual KetaRoller::OutputDevice* newInstance(QObject* parent) { return new _gen(parent); } \
};

#endif // KETAROLLER_OUTPUTDEVICE_H
