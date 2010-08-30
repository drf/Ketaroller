/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef KETAROLLER_INPUTPORT_H
#define KETAROLLER_INPUTPORT_H

#include <Port.h>
#include <OutputPort.h>
#include <QtCore/QList>
#include <QVariantMap>


namespace KetaRoller {

class OutputPort;


class InputPortPrivate;
/**
 * @brief Main entry point for outgoing data from InputDevices
 *
 * An InputPort is the component which takes care of routing outgoing data to an OutputDevice
 * through an OutputPort. Please read @ref routing_model_sec "routing in KetaRoller" to learn more about
 * Ports and Devices.
 * @par
 * An InputPort can be connected to a set of OutputPorts, which should be compatible with the data sent from
 * this output port. Please read @ref generic_argument_model_sec "the generic argument model" to learn how
 * KetaRoller abstracts data arguments at runtime to allow arbitrary connections between different ports.
 *
 * @section input_port_sample_usage_sec Sample usage of InputPort
 *
 * An InputPort should be instantiated with a set of arguments required by the plugins (see
 * @ref plugins_init_arguments_sec "Plugin arguments" to learn more) and a specific type. Afterwards,
 * it should be associated to an InputDevice and connected with a set of output ports.
 *
 * @code
 * using namespace KetaRoller;
 * InputDevice *idevice = myIDevice();
 * QList< OutputPorts* > oports = myOPorts();
 *
 * QVariantMap args;
 * args.insert("MyRequiredArg", "bla");
 * InputPort *iport = new InputPort(Port::MyType, args);
 * idevice->addOutgoingPort(iport);
 *
 * foreach (OutputPort *out, oports) {
 *      iport->addOutput(out);
 * }
 * @endcode
 *
 * This code takes an existing InputDevice and a set of existing OutputPorts which are compatible with the
 * InputPort we're creating. We create a QVariantMap with a required argument for our port (which will be
 * checked inside InputDevice's validatePort) and afterwards, we associate it with our InputDevice and with
 * our OutputPorts.
 *
 * @sa InputDevice
 * @sa OutputPort
 * @sa OutputDevice
 */
class Q_DECL_EXPORT InputPort : public Port
{
    Q_DECLARE_PRIVATE(InputPort)
    Q_DISABLE_COPY(InputPort)
public:
    /**
     * Creates a new input port.
     *
     * @param type The type of this port
     * @param args A set of arbitrary arguments which will be used by the associated InputDevice.
     */
    InputPort(Port::Type type, const QVariantMap &args = QVariantMap());
    /**
     * Base destructor.
     */
    virtual ~InputPort();

    /**
     * @returns All the OutputPorts connected to this port.
     */
    QList< OutputPort* > outputs() const;

    /**
     * Connects an output port to this InputPort. Please note that no checks are performed, so the ports
     * might be incompatible: an error will be printed whenever data will be transferred to the port if that's the case.
     *
     * @param output A valid OutputPort to be connected to this InputPort.
     */
    void addOutput(OutputPort *output);

    /**
     * Disconnects an existing OutputPort from this InputPort.
     *
     * @param output The port which should be disconnected.
     * @param destroyOutput If true, the disconnected port will be deleted.
     */
    void disconnectOutput(OutputPort *output, bool destroyOutput = true);
    /**
     * Sets the outputs to be @c outputs.
     *
     * @param outputs The outputs of this InputPort
     *
     * @sa addOutput
     */
    void setOutputs(const QList< OutputPort* > &outputs);

    /**
     * Disconnects all of the OutputPorts from this InputPort.
     *
     * @param destroyOutputs If true, the disconnected OutputPorts will be deleted.
     *
     * @sa disconnectOutput
     */
    void disconnect(bool destroyOutputs = true);

    /**
     * @returns The arguments of this port
     */
    QVariantMap args() const;
    /**
     * @returns The type of this port
     */
    Type type() const;

    /**
     * @brief Puts arbitrary data into this port
     *
     * Calling this function will make the port route the given data to the connected outputs.
     * This function uses the @ref generic_argument_model_sec "generic argument model", so for calling it
     * with an argument of type "MyType", you would do:
     *
     * @code
     * MyType data;
     * myport->putData(Q_ARG(MyType, data));
     * @endcode
     *
     * Once done, the port will attempt to call the receiver function with the given argument on the other end:
     * should this fail, an error will be printed into the terminal. In the future this function will probably return
     * a more meaningful error.
     *
     * @note Please remember that the data type passed to this port \b MUST be registered as a metatype with the
     *       Qt's metaobject system. Please read Qt documentation for more information.
     *
     * @param argument A QGenericArgument to be generated with Q_ARG, representing the data to be put into the port.
     */
    void putData(const QGenericArgument &argument);
};

}

Q_DECLARE_METATYPE(KetaRoller::InputPort*)

#endif // KETAROLLER_INPUTPORT_H
