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

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "AbstractDevice.h"

#include "AbstractPluginFactory.h"

#include <QVariantMap>

namespace KetaRoller {
class InputPort;

class InputDevicePrivate;
/**
 * @class InputDevice InputDevice.h
 * @brief Base class for input devices
 *
 * InputDevice is the base class for implementing input devices to be used with
 * KetaRoller. It features a set of methods for handling ports which can be connected
 * to this device.
 *
 * @section handle_ports_input_device_sec Handling ports
 *
 * The whole logic for handling ports is contained into the base InputDevice class, however,
 * you will have to reimplement validatePort to actually determine if your device supports
 * a specific port. For example, in that function you can check if the port type is supported,
 * if some compulsory parameters are present, etc.
 *
 * Still, consider that the I/O logic still happens in InputPort.
 *
 * @sa KetaRoller::InputPort
 *
 */
class Q_DECL_EXPORT InputDevice : public AbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(InputDevice)
    Q_DISABLE_COPY(InputDevice)

    Q_PRIVATE_SLOT(d_func(), void removeOutgoingPortDelayed(KetaRoller::InputPort *port, uint mode))

    friend class PluginLoader;

public:
    /**
     * Describes the removal mode of a port in removeOutgoingPort
     */
    enum PortRemovalMode {
        /**
         * The port is not deleted neither disconnected.
         */
        KeepPortAliveMode = 0,
        /**
         * Every output will be disconnected from the port.
         */
        DisconnectOutputsMode = 1,
        /**
         * The input port will be deleted.
         */
        DeleteInputPortMode = 2,
        /**
         * If \c DisconnectOutputsMode has been selected, all of the disconnected outputs will be deleted.
         */
        DeleteAllOrphanOutputsMode = 4
    };
    Q_DECLARE_FLAGS(PortRemovalModes, PortRemovalMode)

    /**
     * Base destructor.
     */
    virtual ~InputDevice();

    /**
     * @returns the input ports connected to this device.
     */
    QList< InputPort* > inputPorts() const;

    /**
     * Attempts to add an outgoing port to this device. The port will be validated.
     *
     * @param port a valid InputPort to be added to this device.
     *
     * @returns \c true if the port has been successfully added, \c false if the device rejected
     *          the port for any reason.
     */
    bool addOutgoingPort(InputPort *port);

    /**
     * Removes an existing port from this device.
     *
     * @param port An existing port of this device to be removed
     * @param mode Defines how the port and its outputs should be treated upon removal. The default
     *             behavior is not to do anything.
     *
     * @sa removeAllOutgoingPorts
     */
    void removeOutgoingPort(InputPort *port, PortRemovalModes mode = KeepPortAliveMode);

    /**
     * Removes all existing ports from this device.
     *
     * @param mode Defines how the ports and their outputs should be treated upon removal. The default
     *             behavior is not to do anything.
     */
    void removeAllOutgoingPorts(PortRemovalModes mode = KeepPortAliveMode);

protected:
    /**
     * Creates a new InputDevice.
     *
     * You cannot use this constructor directly, instead, if you want to create a new InputDevice,
     * please use PluginLoader's methods for loading specific InputDevices.
     *
     * @sa KetaRoller::PluginLoader
     */
    InputDevice(QObject *parent = 0);

    /**
     * @brief Validates a port
     *
     * This function is never meant to be called directly: \c addOutgoingPort will take care of that for you.
     * However, this function \b MUST be reimplemented in plugins implementing an InputDevice.
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
    virtual bool validatePort(KetaRoller::InputPort *port) = 0;

Q_SIGNALS:
    /**
     * This signal will be emitted whenever a port is added to the device
     *
     * @param port The port which has just been added
     *
     * @note Please note that this signal will be emitted only if addOutgoingPort was successful.
     */
    void portAdded(KetaRoller::InputPort *port);
    /**
     * This signal will be emitted whenever a port is removed from the device
     *
     * @param port The port which has just been removed
     *
     * @note Please note that this signal will be emitted \c BEFORE any action eventually specified through
     *       \c PortRemovalModes will take place: however, it is not guaranteed that on the next event loop
     *       run the port will still be a valid object.
     */
    void portRemoved(KetaRoller::InputPort *port);
};

/**
 * @brief Factory for creating InputDevices
 *
 * This class serves as an helper for creating instances of a plugin.
 * It's an internal class and should not be reimplemented directly - please
 * read @ref create_plugins_cmake_sec "CMake's documentation on creating plugins"
 * to learn how to autogenerate plugins.
 * <br><br>
 * Please read @ref plugin_factory_model_sec "the plugin factory model" if you're interested in knowing
 * how PluginFactories work.
 */
class Q_DECL_EXPORT InputDeviceFactory : public AbstractPluginFactory
{
    Q_OBJECT
public:
    InputDeviceFactory(QObject* parent = 0);
    virtual ~InputDeviceFactory();

    virtual InputDevice *newInstance(QObject *parent) = 0;
};

}

Q_DECLARE_INTERFACE(KetaRoller::InputDevice, "org.KetaRoller.InputDevice/0.1")
Q_DECLARE_INTERFACE(KetaRoller::InputDeviceFactory, "org.KetaRoller.InputDeviceFactory/0.1")
Q_DECLARE_OPERATORS_FOR_FLAGS(KetaRoller::InputDevice::PortRemovalModes)

#define KETAROLLER_INPUT_DEVICE_PLUGIN_FACTORY(type, _gen) \
class Q_DECL_EXPORT _gen##Factory : public KetaRoller::InputDeviceFactory \
{ \
    Q_OBJECT \
    Q_INTERFACES(KetaRoller::InputDeviceFactory) \
    Q_DISABLE_COPY(_gen##Factory) \
public: \
    _gen##Factory(QObject* parent = 0) : KetaRoller::InputDeviceFactory(parent) {} \
    ~_gen##Factory() {} \
    virtual KetaRoller::InputDevice* newInstance(QObject* parent) { return new _gen(parent); } \
};

#endif // INPUTDEVICE_H
