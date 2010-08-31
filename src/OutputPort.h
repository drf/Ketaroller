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

#ifndef KETAROLLER_OUTPUTPORT_H
#define KETAROLLER_OUTPUTPORT_H

#include <Port.h>
#include "AbstractPluginFactory.h"

#include <QtPlugin>
#include <QDebug>


namespace KetaRoller {

class OutputPortPrivate;
/**
 * @brief Main entry point for incoming data from InputDevices
 *
 * An OutputPort is the component which takes care of receiving incoming data from an InputDevice
 * through an InputPort. Please read @ref routing_model_sec "routing in KetaRoller" to learn more about
 * Ports and Devices.
 * <br><br>
 * An OutputPort can be connected to a singli InputPort, which should be compatible with the data
 * this output port is capable of handling. Please read @ref generic_argument_model_sec "the generic argument model" to learn how
 * KetaRoller abstracts data arguments at runtime to allow arbitrary connections between different ports.
 * <br><br>
 * When reimplementing this class in your plugin, you will need to add one method as a private slot, receiveData.
 * This is explained in @ref creating_output_port_plugin_sec "creating an OutputPort".
 *
 * @sa InputDevice
 * @sa InputPort
 * @sa OutputDevice
 */
class Q_DECL_EXPORT OutputPort : public Port, public QObject
{
    Q_DECLARE_PRIVATE(OutputPort)
    Q_DISABLE_COPY(OutputPort)

    friend class InputPort;
public:
    /**
     * Base destructor
     */
    virtual ~OutputPort();

    /**
     * @brief Sends arbitrary data to the associated device
     *
     * Calling this function will make the port route the given data to the connected device.
     * This function uses the @ref generic_argument_model_sec "generic argument model", so for calling it
     * with an argument of type "MyType", you would do:
     *
     * @code
     * MyType data;
     * myport->sendToDevice(Q_ARG(MyType, data));
     * @endcode
     *
     * Once done, the port will attempt to call the receiver function with the given argument on the other end:
     * should this fail, an error will be printed into the terminal. In the future this function will probably return
     * a more meaningful error.
     *
     * @note Please remember that the data type passed to this port \b MUST be registered as a metatype with the
     *       Qt's metaobject system. Please read Qt documentation for more information.
     *
     * @param argument A QGenericArgument to be generated with Q_ARG, representing the data to be passed to the device.
     */
    void sendToDevice(const QGenericArgument &arg);

protected:
    /**
     * Base constructor
     */
    explicit OutputPort(Port::Type type, QObject *parent = 0);

    PortPrivate * const d_ptr;

    friend class OutputDevice;
    friend class PluginLoader;
};

/**
 * @brief Factory for creating OutputPorts
 *
 * This class serves as an helper for creating instances of a plugin.
 * It's an internal class and should not be reimplemented directly - please
 * read @ref create_plugins_cmake_sec "CMake's documentation on creating plugins"
 * to learn how to autogenerate plugins.
 * <br><br>
 * Please read @ref plugin_factory_model_sec "the plugin factory model" if you're interested in knowing
 * how PluginFactories work.
 */
class Q_DECL_EXPORT OutputPortFactory : public AbstractPluginFactory
{
    Q_OBJECT
public:
    OutputPortFactory(QObject* parent = 0);
    virtual ~OutputPortFactory();

    virtual OutputPort *newInstance(QObject *parent);
};

}



Q_DECLARE_INTERFACE(KetaRoller::OutputPort, "org.ketamina.OutputPort/0.1")
Q_DECLARE_INTERFACE(KetaRoller::OutputPortFactory, "org.ketamina.OutputPortFactory/0.1")

#define KETAROLLER_OUTPUT_PORT_PLUGIN_FACTORY(type, _gen) \
class Q_DECL_EXPORT _gen##Factory : public KetaRoller::OutputPortFactory \
{ \
    Q_OBJECT \
    Q_INTERFACES(KetaRoller::OutputPortFactory) \
    Q_DISABLE_COPY(_gen##Factory) \
public: \
    _gen##Factory(QObject* parent = 0) : KetaRoller::OutputPortFactory(parent) {} \
    virtual KetaRoller::OutputPort* newInstance(QObject* parent) { return new _gen(parent); } \
};

#endif
