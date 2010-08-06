#ifndef MIDIINPUTEDEVICE_H
#define MIDIINPUTEDEVICE_H

#include <cstdlib>
#include "RtMidi.h"
#include "InputDevice.h"
#include "MIDIMessage.h"

#include <QtCore/QThread>

class MIDIInputDevice : public KetaRoller::InputDevice
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::InputDevice)
    Q_DISABLE_COPY(MIDIInputDevice)

public:
    MIDIInputDevice(QObject* parent = 0);
    virtual ~MIDIInputDevice();

    void getMessage();

private:
    RtMidiIn *midiReceiver;

    std::vector<unsigned char> rawMessage;
    MIDIMessage *message;

    double stamp;
    int nBytes;
};

#endif // MIDIINPUTEDEVICE_H
