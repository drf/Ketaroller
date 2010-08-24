
#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include "MIDIInputDevice.h"


MIDIInputDevice::MIDIInputDevice(QObject* parent)
    :InputDevice(parent)
{
    // RtMidiIn constructor
    try {
      midiReceiver = new RtMidiIn();
    }
    catch ( RtError &error ) {
      error.printMessage();
      exit( EXIT_FAILURE );
    }

    //Open RtMidiIn port
    try {
      midiReceiver->openPort();
    }
    catch ( RtError &error ) {
      error.printMessage();
      delete midiReceiver;
    }
}

MIDIInputDevice::~MIDIInputDevice()
{
}

void MIDIInputDevice::getMessage()
{
    std::vector<unsigned char> rawMessage;
    stamp = midiReceiver->getMessage( &rawMessage );
    MIDIMessage message = MIDIMessageFactory::generateMidiMessage(rawMessage);
}
