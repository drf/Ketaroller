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

#include "tuioportstofiducialstest.h"

#include <KetaRoller/InputDevice>
#include <KetaRoller/InputPort>
#include <KetaRoller/OutputPort>
#include <KetaRoller/PluginLoader>

#define REACTIVISION_OBJECT_ID 2
#include "../../plugins/tuio/FiducialObject.h"

TestOutputDevice::TestOutputDevice(TuioPortsToFiducialsTest* parent)
        : OutputDevice(parent)
        , q(parent)
{
    qDebug() << "A test output device has been created";
}

TestOutputDevice::~TestOutputDevice()
{

}

void TestOutputDevice::init(const QVariantMap& args)
{
    for (int i = 0; i < 4; ++i) {
        m_times[i].start();
    }
    qDebug() << "A test output device has been initialized";
}

bool TestOutputDevice::validatePort(KetaRoller::OutputPort* port)
{
    return true;
}

void TestOutputDevice::newDataFromPort(KetaRoller::OutputPort *port, const FiducialObject& obj)
{
    switch (obj.event()) {
        case FiducialObject::FiducialAddedEvent:
            qDebug() << "Port " << q->m_outputs[port] << " reported a fiducial has been added";
            break;
        case FiducialObject::FiducialRemovedEvent:
            qDebug() << "Port " << q->m_outputs[port] << " reported a fiducial has been removed";
            break;
        case FiducialObject::FiducialUpdatedEvent:
            if (m_times[q->m_outputs[port]].elapsed() > 1000) {
                qDebug() << "Port " << q->m_outputs[port] << " reported a fiducial has been updated:"
                         << "Angle degrees: " << obj.angleDegrees() << "Position:" << obj.position()
                         << "Speed: " << obj.motionSpeed() << "Acceleration: " << obj.motionAcceleration();
                m_times[q->m_outputs[port]].restart();
            }
            break;
        default:
            qWarning() << "Got a fiducial with unknown event";
    }
}

void TestOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, const MIDIMessage& msg)
{

}

void TuioPortsToFiducialsTest::initTestCase()
{
    using namespace KetaRoller;

    m_device = PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::TuioType);
    InputDevice *midiDevice = PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::MIDIType);
    InputPort *midiPort = new InputPort(KetaRoller::Port::MIDIType);
    OutputPort *midiOutputPort = PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::MIDIType);
    midiPort->addOutput(midiOutputPort);
    midiDevice->addOutgoingPort(midiPort);

    QVERIFY(m_device);

    m_outputDevice = new TestOutputDevice(this);
    m_outputDevice->addIncomingPort(midiOutputPort);

    for (int i = 0; i < 4; ++i) {
        OutputPort *port = PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::TuioType);

        QVERIFY(port);
        qDebug() << port;

        QVERIFY(m_outputDevice->addIncomingPort(port));

        m_outputs.insert(port, i);
    }

    for (int i = 30; i < 33; ++i) {
        QVariantMap args;
        args.insert("TuioFiducialID", i);

        KetaRoller::InputPort *input = new InputPort(KetaRoller::Port::TUIOType, args);

        QVERIFY(input);

        QVERIFY(m_device->addOutgoingPort(input));

        if (i == 30) {
            input->addOutput(m_outputs.key(0));
            input->addOutput(m_outputs.key(1));
        } else {
            input->addOutput(m_outputs.key(i-30+1));
        }

        m_inputs.insert(input, i);
    }

    qDebug() << "*************";
    qDebug() << "Test case initialized";
    qWarning() << "This is a manual test case which requires a working ReactiVision client and user interaction.";
    qDebug() << "To avoid flooding your terminal, only an update per second per fiducial will be reported.";
    qDebug() << "Please use for this test case fiducials ID 0,1,2. The mapping is:";
    qDebug() << "ID 0 - Input Port 0 -> Output ports 0,1";
    qDebug() << "ID 1 - Input Port 1 -> Output port 2";
    qDebug() << "ID 2 - Input Port 2 -> Output port 3";
    qDebug() << "*************";
}

void TuioPortsToFiducialsTest::startTest()
{
    qDebug() << "You can now move your fiducials to see the reaction on the ports";
    QEventLoop e;
    e.exec();
}

QTEST_MAIN(TuioPortsToFiducialsTest)
#include "tuioportstofiducialstest.moc"
