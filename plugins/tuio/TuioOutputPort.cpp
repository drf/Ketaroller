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

#include "TuioOutputPort.h"


TuioOutputPort::TuioOutputPort(QObject *parent)
        : OutputPort(TUIOType, parent)
{

}

TuioOutputPort::~TuioOutputPort()
{

}

void TuioOutputPort::receiveData(const FiducialObject& message)
{
//     qDebug() << "Processing FiducialObject message..." << message.position().x() << message.position().y() << message.angle();
    m_lastMessages.append(message);

    // Send message to device - act as a transparent proxy...in future it will also do some processing.
    sendToDevice(Q_ARG(FiducialObject, message));
}

FiducialObject TuioOutputPort::lastMessage() const
{
    return m_lastMessages.last();
}
