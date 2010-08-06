#include "MIDIMessage.h"

class MIDIMessage::Data : public QSharedData
{
public:
    Data(){};
    Data(int statusByte, int dataByte1, int dataByte2)
        :status(statusByte)
        ,data1(dataByte1)
        ,data2(dataByte2)
    {
    }
    Data(const Data &other)
        :status(other.status)
        ,data1(other.data1)
        ,data2(other.data2)
    {
    }
    ~Data() {}

//per rendere più snello il messaggio, converrebbe utilizzare degli "unsigned short" al posto degli int...oppure dici che nn serve???
    int status;
    int data1;
    int data2;
};


MIDIMessage::MIDIMessage()
{
    d = new Data();
}

MIDIMessage::MIDIMessage(int statusByte, int dataByte1, int dataByte2)
{
    d = new Data(statusByte, dataByte1, dataByte2);
}

MIDIMessage::MIDIMessage(const MIDIMessage& other)
        : d(other.d)
{
}

MIDIMessage::~MIDIMessage()
{
}

int MIDIMessage::getData1() const
{
    return d->data1;
}

int MIDIMessage::getData2() const
{
    return d->data2;
}

//helper method just for pitch bender messages: in this case the relevant info is a 14bit number, so we have to merge the two data bytes
int MIDIMessage::pitchBendData() const
{
    return (d->data1 << 8) + d->data2;
}

bool MIDIMessage::isANoteOnMessage() const
{
    return d->status == 144;
}

bool MIDIMessage::isANoteOffMessage() const
{
    return d->status == 128;
}

bool MIDIMessage::isAControlChangeMessage() const
{
    return d->status == 176;
}

bool MIDIMessage::isAPitchBenderMessage() const
{
    return d->status == 224;
}
