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

#include "tuioreactivisionmanualtest.h"

#include <InputDevice.h>
#include <InputPort.h>
#include <OutputPort.h>
#include <PluginLoader.h>

void TuioReactivisionManualTest::initTestCase()
{
    using namespace KetaRoller;

    m_device = PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::TuioType);

    QVERIFY(m_device);

    m_output = PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::TuioType);

    QVERIFY(m_output);

    QVariantMap args;
    args.insert("TuioFiducialID", 1);

    m_input = new InputPort(KetaRoller::Port::TUIOType, args);

    QVERIFY(m_input);

    QVERIFY(m_device->addOutgoingPort(m_input));

    m_input->addOutput(m_output);
}

void TuioReactivisionManualTest::testCatchFiducial()
{
    QEventLoop e;
    e.exec();
}


QTEST_MAIN(TuioReactivisionManualTest)
#include "tuioreactivisionmanualtest.moc"
