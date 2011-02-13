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

BctOutputDevice::BctOutputDevice(QObject* parent)
    : OutputDevice(parent)
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
    //KetaRoller::AbstractDevice::init(args);
}

void BctOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, const FiducialObject& obj)
{
    //if (obj.event() == FiducialObject::FiducialAddedEvent) {
        m_lastFiducialPos.insert(obj.id(), obj);
    //}
}

void BctOutputDevice::newDataFromPort(KetaRoller::OutputPort* port, const MIDIMessage& obj)
{
    if (obj.type() == MIDIMessage::NoteOnEvent) {
    } else if (obj.type() == MIDIMessage::NoteOffEvent) {
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
        } else if (gesture->gestureType() == Qt::TapGesture) {
        }
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
        qDebug() << "SDRENG, speed " << speed << " strummed at " << stringLevel << "%";
    } else {
        qDebug() << "Swipe out of bounds";
        qDebug() << swipeLine << stringLine;
    }
}

#include "BctOutputDevice.moc"
