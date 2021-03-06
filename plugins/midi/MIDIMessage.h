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

#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

#include <QtCore/QSharedDataPointer>
#include <QMetaType>
#include <vector>

/**
* @brief Base generic class for accepted MIDI messages.
*
*/

class Q_DECL_EXPORT MIDIMessage
{
public:
    /**
    * The type of the incoming MIDI Message.
    */
    enum Type {
        UnknownEvent = 0,
        NoteOnEvent,
        NoteOffEvent,
        ControlChangeEvent,
        PitchBendEvent
    };

    /**
    * Default constructor.
    */
    MIDIMessage();
    /**
    * Base destructor.
    */
    virtual ~MIDIMessage();

    /**
    * Copy constructor.
    */
    MIDIMessage(const MIDIMessage &other);

    /**
    * Operator "=" overloading.
    */
    MIDIMessage &operator=(const MIDIMessage &rhs);
    /**
    * Operator "==" overloading.
    */
    bool operator==(const MIDIMessage &other) const;

    /**
    * @returns The two generic data fields.
    */
    quint16 data1() const;
    quint16 data2() const;

    /**
    * @returns The message type.
    */
    Type type() const;

protected:
    /**
    * Base constructor
    */
    MIDIMessage(Type messageType, quint16 data1, quint16 data2);

private:
    class Data;
    QSharedDataPointer< Data > d;
};

/**
* @brief MIDI Note On message class: this message is generated when we press the controller key.
*/
class Q_DECL_EXPORT MIDINoteOnEvent : public MIDIMessage
{
public:
    MIDINoteOnEvent();
    MIDINoteOnEvent(const MIDIMessage &message);
    ~MIDINoteOnEvent();

    /**
    * @return The Note number (range 0-127).
    */
    quint16 note() const;
    /**
    * @return The Note On velocity, i.e. the amount of key pressure (range 0-127).
    */
    quint16 velocity() const;

private:
    MIDINoteOnEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

/**
* @brief MIDI Note Off message class: this message is generated when we release the controller key.
*/
class Q_DECL_EXPORT MIDINoteOffEvent : public MIDIMessage
{
public:
    MIDINoteOffEvent();
    MIDINoteOffEvent(const MIDIMessage &message);
    ~MIDINoteOffEvent();

    /**
    * @return The Note number (range 0-127).
    */
    quint16 note() const;
    /**
    * @return The Note Off velocity, i.e. the amount of key release speed (range 0-127).
    */
    quint16 velocity() const;

private:
    MIDINoteOffEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

/**
* @brief MIDI Control Change message class: this message is typical of encoders, faders, knobs in MIDI controllers.
*/
class Q_DECL_EXPORT MIDIControlChangeEvent : public MIDIMessage
{
public:
    MIDIControlChangeEvent();
    MIDIControlChangeEvent(const MIDIMessage &message);
    ~MIDIControlChangeEvent();

    /**
    * @return The Control Change element number (range 0-127).
    */
    quint16 number() const;
    /**
    * @return The Control Change value (range 0-127).
    */
    quint16 value() const;

private:
    MIDIControlChangeEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

/**
* @brief MIDI Pitch Bender message class: this message is generally used to vary the pitch in a continuously manner.
*/
class Q_DECL_EXPORT MIDIPitchBenderEvent : public MIDIMessage
{
public:
    MIDIPitchBenderEvent();
    MIDIPitchBenderEvent(const MIDIMessage &other);
    ~MIDIPitchBenderEvent();

    MIDIPitchBenderEvent &operator=(const MIDIPitchBenderEvent &rhs);
    /**
    * Operator "==" overloading.
    */
    bool operator==(const MIDIPitchBenderEvent &other) const;

    /**
    * @returns The Pitch Bending value (range 0-16384)
    */
    quint16 value() const;

private:
    MIDIPitchBenderEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

/**
* @brief The class which correctly generates MIDIMessages.
*/
class MIDIMessageFactory {
public:
    /**
    * @param rawMessage An array passed directly by the RtMidi receiver,
    * containing the 3-bytes-message as generated by the physical controller.
    *
    * @returns The higher level object containing all the message info.
    */
    static MIDIMessage generateMidiMessage(std::vector<unsigned char> rawMessage);
};

Q_DECLARE_METATYPE(MIDIMessage)
Q_DECLARE_METATYPE(MIDIPitchBenderEvent)
Q_DECLARE_METATYPE(MIDIControlChangeEvent)
Q_DECLARE_METATYPE(MIDINoteOffEvent)
Q_DECLARE_METATYPE(MIDINoteOnEvent)

#endif // MIDIMESSAGE_H
