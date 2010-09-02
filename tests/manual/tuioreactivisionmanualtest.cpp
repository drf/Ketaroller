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

#include "tuioreactivisionmanualtest.h"

#include <KetaRoller/InputDevice>
#include <KetaRoller/InputPort>
#include <KetaRoller/OutputPort>
#include <KetaRoller/PluginLoader>

#define REACTIVISION_OBJECT_ID 2
#include "../../plugins/tuio/FiducialObject.h"

TestOutputDevice::TestOutputDevice(QObject* parent)
        : OutputDevice(parent)
{
    qDebug() << "A test output device has been created";
}

TestOutputDevice::~TestOutputDevice()
{

}

void TestOutputDevice::init(const QVariantMap& args)
{
    m_time.start();
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
            emit fiducialIsOn();
            break;
        case FiducialObject::FiducialRemovedEvent:
            emit fiducialIsOff();
            break;
        case FiducialObject::FiducialUpdatedEvent:
            if (m_time.elapsed() > 1000) {
                qDebug() << "Fiducial updated. Angle degrees: " << obj.angleDegrees() << "Position:" << obj.position()
                         << "Speed: " << obj.motionSpeed() << "Acceleration: " << obj.motionAcceleration();
                m_time.restart();
            }
            emit fiducialHasChanged(obj);
            break;
        default:
            qWarning() << "Got a fiducial with unknown event";
    }
}

void TuioReactivisionManualTest::initTestCase()
{
    using namespace KetaRoller;

    m_device = PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::TuioType);

    QVERIFY(m_device);

    m_output = PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::TuioType);

    QVERIFY(m_output);

    QVariantMap args;
    args.insert("TuioFiducialID", REACTIVISION_OBJECT_ID);

    m_input = new InputPort(KetaRoller::Port::TUIOType, args);

    QVERIFY(m_input);

    QVERIFY(m_device->addOutgoingPort(m_input));

    m_input->addOutput(m_output);

    m_outputDevice = new TestOutputDevice(this);
    QVERIFY(m_outputDevice->addIncomingPort(m_output));

    qDebug() << "*************";
    qDebug() << "Test case initialized";
    qWarning() << "This is a manual test case which requires a working ReactiVision client and user interaction.";
    qDebug() << "To avoid flooding your terminal, only an update per second of your fiducial will be reported.";
    qDebug() << "*************";
}

void TuioReactivisionManualTest::testCatchFiducial()
{
    qDebug() << "Please add the object with ID " << REACTIVISION_OBJECT_ID << "to your reactivision client in 20 seconds.";
    QEventLoop e;
    QTimer t;
    t.start(20000);
    connect(&t, SIGNAL(timeout()), &e, SLOT(quit()));
    connect(m_outputDevice, SIGNAL(fiducialIsOn()), &e, SLOT(quit()));
    e.exec();
    QVERIFY(t.isActive());
    t.stop();
}

void TuioReactivisionManualTest::testUpdateFiducial()
{
    qDebug() << "Now please move your fiducial to trigger at least an update event in 20 seconds";
    QEventLoop e;
    QTimer t;
    t.start(20000);
    connect(&t, SIGNAL(timeout()), &e, SLOT(quit()));
    connect(m_outputDevice, SIGNAL(fiducialHasChanged(FiducialObject)), &e, SLOT(quit()));
    e.exec();
    QVERIFY(t.isActive());
    t.stop();
}

void TuioReactivisionManualTest::testReleaseFiducial()
{
    qDebug() << "Please remove the fiducial from your client in 20 seconds to complete the test successfully";
    QEventLoop e;
    QTimer t;
    t.start(20000);
    connect(&t, SIGNAL(timeout()), &e, SLOT(quit()));
    connect(m_outputDevice, SIGNAL(fiducialIsOff()), &e, SLOT(quit()));
    e.exec();
    QVERIFY(t.isActive());
    t.stop();
}


QTEST_MAIN(TuioReactivisionManualTest)
#include "tuioreactivisionmanualtest.moc"
