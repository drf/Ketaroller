#include "MIDIMessage.h"
#include <vector>

class MIDIMessageData : public QSharedData
{
public:
    MIDIMessageData()
        : type(MIDIMessage::UnknownEvent)
        , data1(0)
        , data2(0)
    {
    };
    MIDIMessageData(MIDIMessage::Type messageType, quint16 dataByte1, quint16 dataByte2)
        :type(messageType)
        ,data1(dataByte1)
        ,data2(dataByte2)
    {
    }
    MIDIMessageData(const MIDIMessageData &other)
        :type(other.type)
        ,data1(other.data1)
        ,data2(other.data2)
    {
    }
    ~MIDIMessageData() {}

    MIDIMessage::Type type;
    quint16 data1;
    quint16 data2;
};

MIDIMessage MIDIMessageFactory::generateMidiMessage(std::vector<unsigned char> rawMessage)
{
    quint32 nBytes = rawMessage.size();
    if ( nBytes > 0 )
    {
        //if the message is a note on/off, control change or pitch bender (control the status byte)
        int type = static_cast<int>(rawMessage[0]);

        quint16 statusByte = static_cast<quint16>(rawMessage[0]);
        quint16 dataByte1 = static_cast<quint16>(rawMessage[1]);
        quint16 dataByte2 = static_cast<quint16>(rawMessage[2]);

        switch (type) {
            case 128:
                return MIDINoteOffEvent(dataByte1, dataByte2);
                break;
            case 144:
                return MIDINoteOnEvent(dataByte1, dataByte2);
                break;
            case 176:
                return MIDIControlChangeEvent(dataByte1, dataByte2);
                break;
            case 224:
                return MIDIPitchBenderEvent(dataByte1, dataByte2);
                break;
            default:
                break;
        }
    } else {
        // Iddio
    }

    return MIDIMessage();
}

///// MIDI Generic Message

MIDIMessage::MIDIMessage()
        : d(new MIDIMessageData)
{
}

MIDIMessage::MIDIMessage(MIDIMessage::Type messageType, quint16 data1, quint16 data2)
        : d(new MIDIMessageData(messageType, data1, data2))
{

}

MIDIMessage::MIDIMessage(const MIDIMessage& other)
        : d(other.d)
{
}

MIDIMessage::~MIDIMessage()
{
}

quint16 MIDIMessage::data1() const
{
    return d->data1;
}

quint16 MIDIMessage::data2() const
{
    return d->data2;
}

MIDIMessage::Type MIDIMessage::type() const
{
    return d->type;
}

///// Note On

MIDINoteOnEvent::MIDINoteOnEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::NoteOnEvent, data1, data2)
{
}

MIDINoteOnEvent::~MIDINoteOnEvent()
{
}

quint16 MIDINoteOnEvent::note() const
{
    return data1();
}

quint16 MIDINoteOnEvent::velocity() const
{
    return data2();
}

///// Note Off

MIDINoteOffEvent::MIDINoteOffEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::NoteOffEvent, data1, data2)
{
}

MIDINoteOffEvent::~MIDINoteOffEvent()
{
}

quint16 MIDINoteOffEvent::note() const
{
    return data1();
}

quint16 MIDINoteOffEvent::velocity() const
{
    return data2();
}

///// Control Change

MIDIControlChangeEvent::MIDIControlChangeEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::ControlChangeEvent, data1, data2)
{
}

MIDIControlChangeEvent::~MIDIControlChangeEvent()
{
}

quint16 MIDIControlChangeEvent::number() const
{
    return data1();
}

quint16 MIDIControlChangeEvent::value() const
{
    return data2();
}

///// Pitch Bend

MIDIPitchBenderEvent::MIDIPitchBenderEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::PitchBendEvent, data1, data2)
{
}

MIDIPitchBenderEvent::~MIDIPitchBenderEvent()
{
}

quint16 MIDIPitchBenderEvent::value() const
{
    return (data1() << 8) + data2();
}

