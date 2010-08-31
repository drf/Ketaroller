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
 * @par
 * You need this kind of device in order to receive and route MIDI messages from an ordinary
 * (real or virtual) MIDI controller.
 * @par
 * MIDIInputDevice uses 3rd party RtMidi framework (Gary P. Scavone, McGill University) to obtain
 * realtime MIDI input facilities.
 * @par
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
    * @par
    * This function does not block: if a MIDI message is available in the queue, this is decoded and his relevant
    * info are put in a new generated MIDIMessage object; then it is put on the relative MIDIInputDevice port.
    * When no MIDI message is available, the function creates an empty object.
    *
    */
    void getMessage();

protected:
    /**
    * @brief Initialize the MIDIInputDevice.
    *
    * This function creates an RtMidi receiver and open a MIDI input connection
    * (on the OS level, the default or first MIDI port found is opened).
    *
    * @note Just 4 types of incoming message are accepted: NoteOn, NoteOff, PitchBender and ControlChange
    * (system exclusive, timing, active sensing, program change and bank change messages are ignored).
    * Check your MIDI controller!
    *
    * @param args A skip-list-based dictionary with variant value type (not yet used).
    */
    virtual void init(const QVariantMap& args = QVariantMap());

    /**
    * Check if a port is a MIDI port, otherwise an error will be printed into the terminal.
    *
    * @param port The port which should be validated
    *
    * @returns \c true if the port is a MIDI port and can be added to the device, \c false otherwise.
    */
    virtual bool validatePort(KetaRoller::InputPort* port);

private:
    RtMidiIn *midiReceiver;

    double stamp;
    int nBytes;
};

#endif // MIDIINPUTEDEVICE_H
