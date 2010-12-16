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

#include "midimanualtest.h"

#include <KetaRoller/InputDevice>
#include <KetaRoller/InputPort>
#include <KetaRoller/OutputPort>
#include <KetaRoller/PluginLoader>

#include "../../plugins/midi/MIDIMessage.h"

MIDITestOutputDevice::MIDITestOutputDevice(QObject* parent)
        : OutputDevice(parent)
{
    qDebug() << "A test output device has been created";
}

MIDITestOutputDevice::~MIDITestOutputDevice()
{

}

void MIDITestOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, const MIDIObject& obj)
{

}

bool MIDITestOutputDevice::validatePort(KetaRoller::OutputPort* port)
{

}


void MIDITestOutputDevice::init(const QVariantMap& args)
{
    KetaRoller::AbstractDevice::init(args);
}

void MIDIManualTest::initTestCase()
{

}

void MIDIManualTest::testCatchMessage()
{

}

QTEST_MAIN(MIDIManualTest)
#include "midimanualtest.moc"
