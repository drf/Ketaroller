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

#include "testmidiports.h"

#include <KetaRoller/PluginLoader>
#include <KetaRoller/InputPort>

#include "../plugins/midi/MIDIOutputPort.h"

#include <vector>

void TestMIDIPorts::initTestCase()
{
    using namespace KetaRoller;

    OutputPort *port = PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::MIDIType);

    QVERIFY(port);

    m_midiport = qobject_cast< MIDIOutputPort* >(port);

    QVERIFY(m_midiport);

    m_inputport = new InputPort(KetaRoller::Port::MIDIType);

    QVERIFY(m_inputport);
}

void TestMIDIPorts::testPortConnection()
{
    QCOMPARE(m_inputport->outputs().size(), 0);

    m_inputport->addOutput(m_midiport);

    QCOMPARE(m_inputport->outputs().size(), 1);
    QCOMPARE(m_inputport->outputs().first(), m_midiport);
}

void TestMIDIPorts::testMIDICC()
{
    std::vector<unsigned char> rawFakeMessage(3);
    rawFakeMessage[0] = 176;
    rawFakeMessage[1] = (int)(qrand() % 127 + 1);
    rawFakeMessage[2] = (int)(qrand() % 127 + 1);

    MIDIMessage message = MIDIMessageFactory::generateMidiMessage(rawFakeMessage);

    QCOMPARE(message.type(), MIDIMessage::ControlChangeEvent);

    m_inputport->putData(Q_ARG(MIDIMessage, message));

    QCOMPARE(m_midiport->lastMessage(), message);
}

void TestMIDIPorts::testMIDINoteOff()
{
    std::vector<unsigned char> rawFakeMessage(3);
    rawFakeMessage[0] = 128;
    rawFakeMessage[1] = (int)(qrand() % 127 + 1);
    rawFakeMessage[2] = (int)(qrand() % 127 + 1);

    MIDIMessage message = MIDIMessageFactory::generateMidiMessage(rawFakeMessage);

    QCOMPARE(message.type(), MIDIMessage::NoteOffEvent);

    m_inputport->putData(Q_ARG(MIDIMessage, message));

    QCOMPARE(m_midiport->lastMessage(), message);
}

void TestMIDIPorts::testMIDINoteOn()
{
    std::vector<unsigned char> rawFakeMessage(3);
    rawFakeMessage[0] = 144;
    rawFakeMessage[1] = (int)(qrand() % 127 + 1);
    rawFakeMessage[2] = (int)(qrand() % 127 + 1);

    MIDIMessage message = MIDIMessageFactory::generateMidiMessage(rawFakeMessage);

    QCOMPARE(message.type(), MIDIMessage::NoteOnEvent);

    m_inputport->putData(Q_ARG(MIDIMessage, message));

    QCOMPARE(m_midiport->lastMessage(), message);
}

void TestMIDIPorts::testPitchBend()
{
    std::vector<unsigned char> rawFakeMessage(3);
    rawFakeMessage[0] = 224;
    rawFakeMessage[1] = 2;
    int data2 = (int)(qrand() % 127 + 1);
    rawFakeMessage[2] = data2;

    MIDIMessage message = MIDIMessageFactory::generateMidiMessage(rawFakeMessage);

    QCOMPARE(message.type(), MIDIMessage::PitchBendEvent);

    m_inputport->putData(Q_ARG(MIDIMessage, message));

    QCOMPARE(m_midiport->lastMessage(), message);

    MIDIPitchBenderEvent event = static_cast< MIDIPitchBenderEvent >(message);

    quint16 expectedValue = 256 + data2;
    QCOMPARE(event.value(), expectedValue);
}


QTEST_MAIN(TestMIDIPorts)
#include "testmidiports.moc"