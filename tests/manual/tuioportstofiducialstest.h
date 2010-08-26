/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef TUIOPORTSTOFIDUCIALSTEST_H
#define TUIOPORTSTOFIDUCIALSTEST_H

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

class TuioPortsToFiducialsTest;

class TestOutputDevice : public KetaRoller::OutputDevice
{
    Q_OBJECT
public:
    TestOutputDevice(TuioPortsToFiducialsTest* parent = 0);
    virtual ~TestOutputDevice();

    virtual void init(const QVariantMap& args = QVariantMap());
    virtual bool validatePort(KetaRoller::OutputPort* port);

public slots:
    void newDataFromPort(KetaRoller::OutputPort *port, const FiducialObject &obj);

private:
    QHash<int, QTime> m_times;
    TuioPortsToFiducialsTest *q;
};


class TuioPortsToFiducialsTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void startTest();

public:
    KetaRoller::InputDevice *m_device;
    QHash<KetaRoller::InputPort*, int> m_inputs;
    QHash<KetaRoller::OutputPort*, int> m_outputs;
    TestOutputDevice *m_outputDevice;
};

#endif // TUIOPORTSTOFIDUCIALSTEST_H
