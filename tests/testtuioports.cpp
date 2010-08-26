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

#include "testtuioports.h"

#include <PluginLoader.h>
#include <InputPort.h>

#include "../plugins/tuio/TuioOutputPort.h"
#include <TuioObject.h>

void TestTuioPorts::initTestCase()
{
    using namespace KetaRoller;

    OutputPort *port = PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::TuioType);

    QVERIFY(port);

    m_tuioport = qobject_cast< TuioOutputPort* >(port);

    QVERIFY(m_tuioport);

    m_inputport = new InputPort(KetaRoller::Port::TUIOType);

    QVERIFY(m_inputport);
}

void TestTuioPorts::testPortConnection()
{
    QCOMPARE(m_inputport->outputs().size(), 0);

    m_inputport->addOutput(m_tuioport);

    QCOMPARE(m_inputport->outputs().size(), 1);
    QCOMPARE(m_inputport->outputs().first(), m_tuioport);
}

void TestTuioPorts::testTuioMessage()
{
    TUIO::TuioObject *randObj = new TUIO::TuioObject(qrand(), qrand(), 1/qrand(), 1/qrand(), 1/qrand());
    FiducialObject fiducial(randObj);

    m_inputport->putData(Q_ARG(FiducialObject, fiducial));

    QCOMPARE(m_tuioport->lastMessage(), fiducial);
}

QTEST_MAIN(TestTuioPorts)
#include "testtuioports.moc"
