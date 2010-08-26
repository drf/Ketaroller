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

#include "TuioOutputPort.h"

TuioOutputPort::TuioOutputPort()
        : OutputPort(TUIOType)
{

}

TuioOutputPort::~TuioOutputPort()
{

}

FiducialObject TuioOutputPort::lastMessage() const
{
    return m_lastMessages.last();
}

void TuioOutputPort::receiveData(const FiducialObject& message)
{
    m_lastMessages.append(message);

    // Send message to device - act as a transparent proxy
    sendToDevice(Q_ARG(FiducialObject, message));
}

Q_EXPORT_PLUGIN2(ketaroller_tuio_output_port, TuioOutputPort)
