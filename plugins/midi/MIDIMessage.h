#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

#include <exception>

#include <QtCore/QSharedDataPointer>

//Exception for invalid MIDI Messages

/*  ? proof with Qt Exception ?
class MIDINoteException : public QtConcurrent::Exception
{
public:
    void raise() const { throw *this; }
    MIDINoteException *clone() const { return new MIDINoteException(*this); }
};
*/

class MIDINoteException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Invalid MIDI Message";
  }
} MIDINoteEx;

//?????? TU COME DIRESTI DI FARE DARIA ???????? Io ho provato così...

//MIDIInputDevice accept 4 types of MIDI Message: Note On, Note Off, Control Change and Pitch Bender.
//Inheritance from a single "abstract class" to separate and distinguish different message types is quite useless, because they all have the same structure and properties.
//So there is a single MIDIMessage class, and 4 boolean methods to check the message type.
//In this way an hypothetical receiver of this MIDIMessage is loosely coupled from the sender, beacuse he does not have to know the implementation of the MIDI protocol (in this case the relation between status byte and message type).

class MIDIMessage
{

public:
    MIDIMessage();
    MIDIMessage(int status, int data1, int data2);
    MIDIMessage(const MIDIMessage &other);
    ~MIDIMessage();

    int getData1() const;
    int getData2() const;
    int pitchBendData() const;

    bool isANoteOffMessage() const;
    bool isANoteOnMessage() const;
    bool isAControlChangeMessage() const;
    bool isAPitchBenderMessage() const;

    /*DARIA: per disaccoppiare ancora di più e fare in modo che il ricevitore possa proprio ignorare i data bytes, avevo pensato ad una roba del genere:

    int getNoteNumber() const;
    int getNoteVelocity() const;
    int getControlChangeNumber() const;
    int getControlChangeValue() const;

    in questo modo il ricevitore prima checka il tipo, poi fa la domanda giusta, senza sapere quale dataByte gli occorre.
    Solo che l'implementazione di sti 4 metodi sarebbe identica a quella di getData1 e getData2,
    ed inoltre dal punto di vista della programmazione ad oggetti mi sembra una gran merdata.
    Però sottoclassare MIDIMessage e fare NoteMessage, ControlChangeMessage, ecc...mi sembra veramente inutile
    Il significato di sti cazzo di data byte è diverso (nota, velocity, valore...), ma l'implementazione è identica.
    Boh....tu che dici?
    */

private:
    class Data;
    QSharedDataPointer< Data > d;

};

#endif // MIDIMESSAGE_H
