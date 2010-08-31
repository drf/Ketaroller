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

#ifndef TUIOOUTPUTPORT_H
#define TUIOOUTPUTPORT_H

#include <QtCore/QPointF>

#include <OutputPort.h>
#include "FiducialObject.h"

/**
 * @brief Entry point for incoming data from TuioInputDevices
 *
 * This class takes care of receiving FiducialObject messages from a TuioInputDevice through a compatible InputPort.
 * Please read @ref routing_model_sec "routing in KetaRoller" to learn more about Ports and Devices and
 * @ref creating_output_port_plugin_sec "creating an OutputPort".
 *
 * @sa OutputPort
 * @sa OutputDevice
 * @sa FiducialObject
 * @sa TuioInputDevice
 */
class Q_DECL_EXPORT TuioOutputPort : public KetaRoller::OutputPort
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::OutputPort)
    Q_DISABLE_COPY(TuioOutputPort)
public:
    /**
    * Base constructor
    */
    TuioOutputPort(QObject *parent);
    /**
    * Base destructor.
    */
    virtual ~TuioOutputPort();

    /**
    * @returns The last FiducialObject message received.
    */
    FiducialObject lastMessage() const;

public slots:
    /**
    * This function receive and store the FiducialObject messages passed by the TuioInputDevice through the InputPort.
    *
    * @param message The reference to a FiducialObject passed by the input.
    */
    void receiveData(const FiducialObject &message);

private:
    QList< FiducialObject > m_lastMessages;
};

#endif // TUIOOUTPUTPORT_H
