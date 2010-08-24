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

class MIDIOutputPort : public KetaRoller::OutputPort
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::OutputPort)
    Q_DISABLE_COPY(MIDIOutputPort)
public:
    MIDIOutputPort();
    virtual ~MIDIOutputPort();

    void processMIDIMessage(const MIDIMessage &message);

    MIDIMessage lastMessage() const;

private:
    QList< MIDIMessage > m_lastMessages;
};

template<> inline void ketaroller_onNewData< MIDIMessage >(const MIDIMessage &data, KetaRoller::OutputPort *port) {
    qDebug() << "FIST DA MIDI WITH DA MESSAGE" << data.type();

    MIDIOutputPort *realPort = qobject_cast< MIDIOutputPort* >(port);
    realPort->processMIDIMessage(data);
}

#endif // MIDIOUTPUTPORT_H
