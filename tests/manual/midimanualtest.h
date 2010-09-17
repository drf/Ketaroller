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

#ifndef MIDIMANUALTEST_H
#define MIDIMANUALTEST_H

#include <QObject>

#include <QtTest/QtTest>
#include <KetaRoller/OutputDevice>

class MIDIObject;
namespace KetaRoller {
class InputDevice;
class InputPort;
class OutputPort;
class OutputPort;
}

class MIDITestOutputDevice : public KetaRoller::OutputDevice
{
    Q_OBJECT
public:
    MIDITestOutputDevice(QObject* parent = 0);
    virtual ~MIDITestOutputDevice();

    virtual void init(const QVariantMap& args = QVariantMap());
    virtual bool validatePort(KetaRoller::OutputPort* port);

public slots:
    void newDataFromPort(KetaRoller::OutputPort *port, const MIDIObject &obj);

signals:
    void messageReceived();

private:
    QTime m_time;
};

class MIDIManualTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testCatchMessage();

private:
    KetaRoller::InputDevice *m_device;
    KetaRoller::InputPort *m_input;
    KetaRoller::OutputPort *m_output;
    MIDITestOutputDevice *m_outputDevice;
};

#endif // MIDIMANUALTEST_H
