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

#ifndef TUIOREACTIVISIONMANUALTEST_H
#define TUIOREACTIVISIONMANUALTEST_H

#include <QtGui>
#include <QtTest/QtTest>

#include <OutputDevice.h>

class FiducialObject;
namespace KetaRoller {
class InputDevice;
class InputPort;
class OutputPort;
class OutputPort;
}

class TestOutputDevice : public KetaRoller::OutputDevice
{
    Q_OBJECT
public:
    TestOutputDevice(QObject* parent = 0);
    virtual ~TestOutputDevice();

    virtual void init(const QVariantMap& args = QVariantMap());
    virtual bool validatePort(KetaRoller::OutputPort* port);

public slots:
    void newDataFromPort(KetaRoller::OutputPort *port, const FiducialObject &obj);

signals:
    void fiducialIsOn();
    void fiducialHasChanged(FiducialObject);
    void fiducialIsOff();

private:
    QTime m_time;
};

class TuioReactivisionManualTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testCatchFiducial();
    void testUpdateFiducial();
    void testReleaseFiducial();

private:
    KetaRoller::InputDevice *m_device;
    KetaRoller::InputPort *m_input;
    KetaRoller::OutputPort *m_output;
    TestOutputDevice *m_outputDevice;
};

#endif // TUIOREACTIVISIONMANUALTEST_H
