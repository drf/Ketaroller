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

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include "MIDIInputDevice.h"
#include <InputPort.h>

#include <QtPlugin>

struct DynData {
    MIDIInputDevice *device;
};

void messageCallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
    std::vector< unsigned char > realMessage;
    unsigned int nBytes = message->size();
    for ( unsigned int i=0; i<nBytes; i++ ) {
        realMessage.push_back((uchar)message->at(i));
    }

    DynData *data = (DynData*)userData;
    data->device->getMessage(realMessage);
}

MIDIInputDevice::MIDIInputDevice(QObject* parent)
    : InputDevice(parent)
{
}

MIDIInputDevice::~MIDIInputDevice()
{
    midiReceiver->closePort();
}

void MIDIInputDevice::init(const QVariantMap& args)
{
    qRegisterMetaType<MIDIMessage>();
    qRegisterMetaType<MIDINoteOffEvent>();
    qRegisterMetaType<MIDINoteOnEvent>();
    qRegisterMetaType<MIDIControlChangeEvent>();
    qRegisterMetaType<MIDIPitchBenderEvent>();

    QString clientName = "KetaRoller";
    if (args.contains("ClientName")) {
        clientName = args.value("ClientName").toString();
    }

    // RtMidiIn constructor
    try {
        midiReceiver = new RtMidiIn(QString("%1 Input Client").arg(clientName).toStdString());
    } catch ( RtError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    unsigned int nPorts = midiReceiver->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";

    DynData *data = new DynData;
    data->device = this;

    midiReceiver->setCallback( &messageCallback, data );

    try {
        midiReceiver->openVirtualPort(QString("%1 Input Port 0").arg(clientName).toStdString());
    } catch ( RtError &error ) {
        error.printMessage();
        delete midiReceiver;
    }

    // Ignore sysex, timing, or active sensing messages.
    midiReceiver->ignoreTypes(true, true, true);
}

bool MIDIInputDevice::validatePort(KetaRoller::InputPort* port)
{
    if (port->type() != KetaRoller::InputPort::MIDIType) {
        qDebug() << "This device is capable of handling MIDI ports only";
        return false;
    }

    return true;
}

void MIDIInputDevice::getMessage(std::vector< unsigned char > rawMessage)
{
    MIDIMessage message = MIDIMessageFactory::generateMidiMessage(rawMessage);

    foreach (KetaRoller::InputPort *port, inputPorts()) {
        port->putData(Q_ARG(MIDIMessage, message));
    }
}

#include "MIDIInputDevice.moc"
