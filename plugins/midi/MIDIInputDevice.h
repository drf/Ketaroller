#ifndef MIDIINPUTEDEVICE_H
#define MIDIINPUTEDEVICE_H

#include <cstdlib>
#include "RtMidi.h"
#include "InputDevice.h"
#include "MIDIMessage.h"

#include <QtCore/QThread>

/**
 * @brief Class for MIDI input devices
 *
 * MIDIInputDevice is the MIDI implementation of InputDevice class.
 * <br /><br />
 * You need this kind of device in order to receive and route MIDI messages from an ordinary
 * (real or virtual) MIDI controller.
 * <br /><br />
 * MIDIInputDevice uses 3rd party RtMidi framework (Gary P. Scavone, McGill University) to obtain
 * realtime MIDI input facilities.
 * <br /><br />
 * Still, consider that the whole logic for handling ports is contained into the InputDevice class.
 *
 * @sa KetaRoller::InputDevice
 *
 */

class Q_DECL_EXPORT MIDIInputDevice : public KetaRoller::InputDevice
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::InputDevice)
    Q_DISABLE_COPY(MIDIInputDevice)

public:
    /**
     * Base costructor
     */
    MIDIInputDevice(QObject* parent = 0);

    /**
     * Base destructor
     */
    virtual ~MIDIInputDevice();

    /**
    * @brief Reads a raw MIDI message, generates a MIDIMessage object and puts it on the relative port.
    *
    * This function read an incoming raw message from the MIDI input queue: the max queue size is 1024.
    * If the maximum queue size limit is reached, subsequent incoming MIDI messages are discarded
    * until the queue size is reduced.
    * <br /><br />
    * This function is not blocking: if a MIDI message is available in the queue, it is decoded and its relevant
    * info are put in a newly generated MIDIMessage object; it is then put on the relative MIDIInputDevice port.
    * When no MIDI messages are available, the function creates an empty object.
    *
    */
    void getMessage();

protected:
    /**
    * @brief Initialize the MIDIInputDevice.
    *
    * This function creates an RtMidi receiver and opens a MIDI input connection
    * (on the OS level, the default or first MIDI port found is opened).
    *
    * @note Just 4 types of incoming message are accepted: NoteOn, NoteOff, PitchBender and ControlChange
    * (system exclusive, timing, active sensing, program change and bank change messages are ignored).
    * Check your MIDI controller!
    */
    virtual void init(const QVariantMap& args = QVariantMap());

    virtual bool validatePort(KetaRoller::InputPort* port);

private:
    RtMidiIn *midiReceiver;

    double stamp;
    int nBytes;
};

#endif // MIDIINPUTEDEVICE_H
