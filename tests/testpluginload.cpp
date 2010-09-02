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

#include "testpluginload.h"

#include <KetaRoller/PluginLoader>
#include <KetaRoller/InputDevice>

void TestPluginLoad::initTestCase()
{
    KetaRoller::PluginLoader::instance();
}

void TestPluginLoad::testLoadMidiInputDevice()
{
    QVERIFY(KetaRoller::PluginLoader::instance());
    KetaRoller::InputDevice *inputDevice = KetaRoller::PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::MIDIType);
    QVERIFY(inputDevice);

    qDebug() << inputDevice;
    qDebug() << inputDevice->uuid();
    qDebug() << inputDevice->inputPorts();

    QCOMPARE(inputDevice->inputPorts().size(), 0);
}

void TestPluginLoad::testLoadMidiOutputPort()
{
    QVERIFY(KetaRoller::PluginLoader::instance());
    KetaRoller::OutputPort *outputPort = KetaRoller::PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::MIDIType);
    QVERIFY(outputPort);
}

QTEST_MAIN(TestPluginLoad)
#include "testpluginload.moc"
