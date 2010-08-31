
#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include "MIDIInputDevice.h"
#include <InputPort.h>

#include <QtPlugin>

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
    Q_UNUSED(args)

    // RtMidiIn constructor
    try {
      midiReceiver = new RtMidiIn();
    } catch ( RtError &error ) {
      error.printMessage();
      exit( EXIT_FAILURE );
    }

    //Open RtMidiIn port
    try {
      midiReceiver->openPort();
    } catch ( RtError &error ) {
      error.printMessage();
      delete midiReceiver;
    }
}

bool MIDIInputDevice::validatePort(KetaRoller::InputPort* port)
{
    if (port->type() != KetaRoller::InputPort::MIDIType) {
        qDebug() << "This device is capable of handling MIDI ports only";
        return false;
    }
}

void MIDIInputDevice::getMessage()
{
    std::vector<unsigned char> rawMessage;
    stamp = midiReceiver->getMessage( &rawMessage );
    MIDIMessage message = MIDIMessageFactory::generateMidiMessage(rawMessage);

    foreach (KetaRoller::InputPort *port, inputPorts()) {
        port->putData(Q_ARG(MIDIMessage, message));
    }
}
