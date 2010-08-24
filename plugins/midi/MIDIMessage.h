#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

#include <QtCore/QSharedDataPointer>
#include <vector>

class Q_DECL_EXPORT MIDIMessage
{
public:
    enum Type {
        UnknownEvent = 0,
        NoteOnEvent,
        NoteOffEvent,
        ControlChangeEvent,
        PitchBendEvent
    };

    MIDIMessage();
    ~MIDIMessage();

    MIDIMessage(const MIDIMessage &other);
    MIDIMessage &operator=(const MIDIMessage &rhs);
    bool operator==(const MIDIMessage &other) const;

    quint16 data1() const;
    quint16 data2() const;
    Type type() const;

protected:
    MIDIMessage(Type messageType, quint16 data1, quint16 data2);

private:
    class Data;
    QSharedDataPointer< Data > d;
};

class Q_DECL_EXPORT MIDINoteOnEvent : public MIDIMessage
{
public:
    ~MIDINoteOnEvent();

    quint16 note() const;
    quint16 velocity() const;

private:
    MIDINoteOnEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

class Q_DECL_EXPORT MIDINoteOffEvent : public MIDIMessage
{
public:
    ~MIDINoteOffEvent();

    quint16 note() const;
    quint16 velocity() const;

private:
    MIDINoteOffEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

class Q_DECL_EXPORT MIDIControlChangeEvent : public MIDIMessage
{
public:
    ~MIDIControlChangeEvent();

    quint16 number() const;
    quint16 value() const;

private:
    MIDIControlChangeEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

class Q_DECL_EXPORT MIDIPitchBenderEvent : public MIDIMessage
{
public:
    MIDIPitchBenderEvent(const MIDIMessage &other);
    ~MIDIPitchBenderEvent();

    MIDIPitchBenderEvent &operator=(const MIDIPitchBenderEvent &rhs);
    bool operator==(const MIDIPitchBenderEvent &other) const;

    quint16 value() const;

private:
    MIDIPitchBenderEvent(quint16 data1, quint16 data2);

    friend class MIDIMessageFactory;
};

class MIDIMessageFactory {
public:
    static MIDIMessage generateMidiMessage(std::vector<unsigned char> rawMessage);
};

#endif // MIDIMESSAGE_H
