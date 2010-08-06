
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
    stamp = midiReceiver->getMessage( &rawMessage );
    nBytes = rawMessage.size();
    if ( nBytes > 0 )
    {
        //if the message is a note on/off, control change or pitch bender (control the status byte)
        if((int)rawMessage[0]==128 || (int)rawMessage[0]==144 || (int)rawMessage[0]==176 || (int)rawMessage[0]==224) {
            //create a new MIDIMessage instance passing status and data bytes
            int statusByte = (int)rawMessage[0];
            int dataByte1 = (int)rawMessage[1];
            int dataByte2 = (int)rawMessage[2];
            message = new MIDIMessage(statusByte, dataByte1, dataByte2);

            /*  ? print check ?
                int i;
                for ( i=0; i<nBytes; i++ )
                        std::cout << "Byte " << i << " = " << (int)rawMessage[i] << ", ";
                std::cout << "stamp = " << stamp << std::endl;
            */
        }
        else throw MIDINoteEx;
    }
}
