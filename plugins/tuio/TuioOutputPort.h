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

#ifndef TUIOOUTPUTPORT_H
#define TUIOOUTPUTPORT_H

#include <QtCore/QPointF>

#include <KetaRoller/OutputPort>
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
    * This function receives and stores the FiducialObject messages passed by the TuioInputDevice through the InputPort.
    * It's a compulsory reimplementation of the data receiver callback as explained in
    * @ref generic_argument_model_sec "the generic argument model". Please read
    * @ref creating_output_port_plugin_sec "creating an OutputPort" for a better overview over this method.
    *
    * @param message The reference to a FiducialObject passed by the input.
    */
    void receiveData(const FiducialObject &message);

private:
    QList< FiducialObject > m_lastMessages;
};

#endif // TUIOOUTPUTPORT_H
