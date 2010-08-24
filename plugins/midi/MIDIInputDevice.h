#ifndef MIDIINPUTEDEVICE_H
#define MIDIINPUTEDEVICE_H

#include <cstdlib>
#include "RtMidi.h"
#include "InputDevice.h"
#include "MIDIMessage.h"

#include <QtCore/QThread>

class Q_DECL_EXPORT MIDIInputDevice : public KetaRoller::InputDevice
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

    double stamp;
    int nBytes;
};

#endif // MIDIINPUTEDEVICE_H
