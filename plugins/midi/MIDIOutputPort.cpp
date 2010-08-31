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

#include "MIDIOutputPort.h"

#include <QDebug>

MIDIOutputPort::MIDIOutputPort(QObject *parent)
        : OutputPort(MIDIType, parent)
{
}

MIDIOutputPort::~MIDIOutputPort()
{

}

void MIDIOutputPort::receiveData(const MIDIMessage& message)
{
    qDebug() << "Processing MIDIMessage..." << message.data1() << message.data2();
    m_lastMessages.append(message);

    // Send message to device - act as a transparent proxy...in future it will also do some processing.
    sendToDevice(Q_ARG(MIDIMessage, message));

}

MIDIMessage MIDIOutputPort::lastMessage() const
{
    return m_lastMessages.last();
}

#include "MIDIOutputPort.moc"
