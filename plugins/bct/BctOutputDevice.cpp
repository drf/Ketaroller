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


#include "BctOutputDevice.h"
#include <KetaRoller/OutputPort>
#include <QGesture>
#include <QTouchEvent>
#include <QLineF>
#include <QApplication>
#include <QDesktopWidget>
#include <QTcpSocket>
#include <QUdpSocket>
#include "bctnetworkprotocol.h"
#include <QByteArray>
#include <QTimer>
#include <QDomDocument>
#include <sys/socket.h>

BctOutputDevice::BctOutputDevice(QObject* parent)
    : OutputDevice(parent)
    , m_udpTimestamp(0)
    , m_screenRect(QApplication::desktop()->rect())
    , m_center(0.5, 0.5)
{
    m_swipeDuration.start();
}

BctOutputDevice::~BctOutputDevice()
{

}

bool BctOutputDevice::validatePort(KetaRoller::OutputPort* port)
{
    if (port->type() != KetaRoller::OutputPort::TUIOType &&
        port->type() != KetaRoller::OutputPort::GestureType &&
        port->type() != KetaRoller::OutputPort::MIDIType) {
        return false;
    } else {
        qDebug() << "Port added";
        return true;
    }
}

void BctOutputDevice::init(const QVariantMap& args)
{
    Q_UNUSED(args);
}

void BctOutputDevice::startConnection(const QHostAddress& address, int port)
{
    m_models.clear();

    if (!m_tcpSocket.isNull()) {
        m_tcpSocket.data()->close();
        m_tcpSocket.data()->deleteLater();
    }

    m_tcpSocket = new QTcpSocket(this);
    qDebug() << "Connecting TCP";
    m_tcpSocket.data()->connectToHost(address, port);
    m_tcpSocket.data()->waitForConnected();

    qDebug() << "Connected";

    BctNetProtocol::tcpSender(m_tcpSocket.data(), QByteArray("list"));
    m_tcpSocket.data()->waitForReadyRead();

    QDomDocument doc("mydocument");

    if (!doc.setContent(BctNetProtocol::tcpReceiver(m_tcpSocket.data()))) {
        qDebug() << "Could not create a document!";
        return;
    }

    QDomElement docElem = doc.documentElement();

    QDomElement n = docElem.firstChildElement("model");
    while(!n.isNull()) {
        // Parse the element
        QString name = n.attribute("name");
        int id = n.attribute("id").toInt();

        QHash< int, QString > parameters;
        QDomElement attr = n.firstChildElement("param");
        while (!attr.isNull()) {
            parameters.insert(attr.attribute("id").toInt(), attr.attribute("name"));
            attr = attr.nextSiblingElement("param");
        }

        ModelDescription desc;
        desc.name = name;
        desc.parameters = parameters;

        m_models.insert(id, desc);

        n = n.nextSiblingElement("model");
    }
}
void BctOutputDevice::mapFiducialEvent(quint16 fiducialId, BctOutputDevice::FiducialEvent event,
                                       int tree, int param, double min, double max)
{
    Mapping mapping;
    mapping.event = event;
    mapping.max = max;
    mapping.min = min;
    mapping.param = param;
    mapping.tree = tree;
    m_fiducialMappings.insert(fiducialId, mapping);
}

void BctOutputDevice::mapMidiCC(quint16 ccName, int tree, int param, double min, double max)
{
    Mapping mapping;
    mapping.max = max;
    mapping.min = min;
    mapping.param = param;
    mapping.tree = tree;
    m_fiducialMappings.insert(ccName, mapping);
}

void BctOutputDevice::mapNoteOnOff(int tree, int paramOn, int paramOff)
{
    OnOffMapping mapping;
    mapping.paramOff = paramOff;
    mapping.paramOn = paramOn;
    m_onOffMappings.insert(tree, mapping);
}

void BctOutputDevice::sendAllNoteOn()
{
    for (QHash< int, OnOffMapping >::const_iterator i = m_onOffMappings.constBegin();
         i != m_onOffMappings.constEnd(); ++i) {
        sendUdpMessage(i.key(), i.value().paramOn, 1);
    }
}

void BctOutputDevice::sendAllNoteOff()
{
    for (QHash< int, OnOffMapping >::const_iterator i = m_onOffMappings.constBegin();
         i != m_onOffMappings.constEnd(); ++i) {
        sendUdpMessage(i.key(), i.value().paramOff, 1);
    }
}

QHash< int, ModelDescription > BctOutputDevice::models() const
{
    return m_models;
}

bool BctOutputDevice::loadModel(int id)
{
    if (!m_tcpSocket.isNull()) {
        BctNetProtocol::tcpSender(m_tcpSocket.data(), QString("load %1").arg(id).toAscii());
        m_tcpSocket.data()->waitForReadyRead();
        return BctNetProtocol::tcpReceiver(m_tcpSocket.data()).toInt() >= 0;
    } else {
        return false;
    }
}

bool BctOutputDevice::startPlaying()
{
    if (!m_tcpSocket) {
        BctNetProtocol::tcpSender(m_tcpSocket.data(), QByteArray("play"));
        m_tcpSocket.data()->waitForReadyRead();
        int port = BctNetProtocol::tcpReceiver(m_tcpSocket.data()).toInt();

        if (port <= 0) {
            return false;
        }

        if (!m_udpSocket.isNull()) {
            m_udpSocket.data()->close();
            m_udpSocket.data()->deleteLater();
        }

        QUdpSocket *udp = new QUdpSocket(this);
        udp->connectToHost(m_tcpSocket.data()->peerAddress(), port);
        udp->waitForConnected();
        qDebug() << "Udp connected";
        return true;
    } else {
        return false;
    }
}

void BctOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, const FiducialObject& obj)
{
    //if (obj.event() == FiducialObject::FiducialAddedEvent) {
    m_lastFiducialPos.insert(obj.id(), obj);
    //}
    if (m_fiducialMappings.contains(obj.id())) {
        Mapping mapping = m_fiducialMappings[obj.id()];
        double value;
        switch (mapping.event) {
            case Angle:
                value = mapping.min + ( (mapping.max - mapping.min) * qBound<double>(0, obj.angle(), 1) );
                sendUdpMessage(mapping.tree, mapping.param, value);
                break;
            case Position:
                break;
        }
    }
}

void BctOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, const MIDIMessage& obj)
{
    if (obj.type() == MIDIMessage::NoteOnEvent) {
        sendAllNoteOn();
    } else if (obj.type() == MIDIMessage::NoteOffEvent) {
        sendAllNoteOff();
    } else if (obj.type() == MIDIMessage::ControlChangeEvent) {
        MIDIControlChangeEvent ccEvent = static_cast< MIDIControlChangeEvent >(obj);
        if (m_midiMappings.contains(ccEvent.number())) {
            Mapping mapping = m_midiMappings[ccEvent.number()];
            double value = mapping.min + (((mapping.max - mapping.min) / 127) * ccEvent.value());
            sendUdpMessage(mapping.tree, mapping.param, value);
        } else {
            qDebug() << "No handler configured for this MIDI CC";
        }
    }
}

void BctOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, QGesture* gesture)
{
    if (gesture->state() == Qt::GestureStarted) {
        m_swipeDuration.restart();
    }
    if (gesture->state() == Qt::GestureCanceled) {
        if (gesture->gestureType() == Qt::SwipeGesture) {
            QPointF normPos = gesture->hotSpot();
            m_lastHotspot = QPointF(normPos.x() / m_screenRect.width(), normPos.y() / m_screenRect.height());
        }
    } else if (gesture->gestureType() == Qt::TapGesture) {

    }
}

void BctOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, QTouchEvent* event)
{
    QLineF swipeLine(event->touchPoints().last().normalizedPos(), m_lastHotspot);
    evaluateSwipe(swipeLine);
}

void BctOutputDevice::evaluateSwipe(QLineF swipeLine)
{
    QLineF stringLine(m_lastFiducialPos.values().first().position(), m_center);
    QPointF intersection;
    if (swipeLine.intersect(stringLine, &intersection) == QLineF::BoundedIntersection) {
        // Play
        int duration = m_swipeDuration.restart();
        qreal length = swipeLine.length();
        uint speed = qBound(1, qRound((length / duration) * 10000), 100);
        QLineF trimmedLine = QLineF(m_center, intersection);
        int stringLevel = qRound((trimmedLine.length() / stringLine.length())*100);

        sendAllNoteOn();

        // Now, depending on the speed, trigger a note off.
        QTimer::singleShot(800 + (32*speed), this, SLOT(sendAllNoteOff()));
    } else {
        qDebug() << "Swipe out of bounds";
        qDebug() << swipeLine << stringLine;
    }
}

void BctOutputDevice::sendUdpMessage(int tree, int control, double value)
{
    ++m_udpTimestamp;

    UdpMessage message;
    message.control = control;
    message.timestamp = m_udpTimestamp;
    message.tree = tree;
    message.value = value;

    BctNetProtocol::udpSender(m_udpSocket.data(), message);
}

#include "BctOutputDevice.moc"
