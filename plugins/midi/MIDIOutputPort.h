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

#ifndef MIDIOUTPUTPORT_H
#define MIDIOUTPUTPORT_H

#include <OutputPort.h>

#include "MIDIMessage.h"


/**
 * @brief Entry point for incoming data from MIDIInputDevices
 *
 * This class takes care of receiving MIDIMessages from a MIDIInputDevice through a compatible InputPort.
 * Please read @ref routing_model_sec "routing in KetaRoller" to learn more about Ports and Devices and
 * @ref creating_output_port_plugin_sec "creating an OutputPort".
 *
 * @sa Ketaroller::OutputPort
 * @sa Ketaroller::OutputDevice
 * @sa MIDIMessage
 * @sa MIDIInputDevice
 */
class Q_DECL_EXPORT MIDIOutputPort : public KetaRoller::OutputPort
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::OutputPort)
    Q_DISABLE_COPY(MIDIOutputPort)
public:
    /**
    * Base constructor
    */
    MIDIOutputPort(QObject *parent);
    /**
    * Base destructor.
    */
    virtual ~MIDIOutputPort();

    /**
    * @returns The last MIDIMessage received.
    */
    MIDIMessage lastMessage() const;

public slots:
    /**
    * This function receives and stores the MIDIMessages passed by the MIDIInputDevice through the InputPort.
    * It's a compulsory reimplementation of the data receiver callback as explained in
    * @ref generic_argument_model_sec "the generic argument model". Please read
    * @ref creating_output_port_plugin_sec "creating an OutputPort" for a better overview over this method.
    *
    * @param message The reference to a MIDIMessage passed by the input.
    */
    void receiveData(const MIDIMessage &message);

private:
    QList< MIDIMessage > m_lastMessages;
};

#endif // MIDIOUTPUTPORT_H
