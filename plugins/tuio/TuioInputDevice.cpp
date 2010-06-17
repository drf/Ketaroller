/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "TuioInputDevice.h"

#include "FiducialObject.h"

#include <QtPlugin>
#include <QRunnable>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGesture>
#include <QDebug>

GrabberWidget::GrabberWidget(QWidget* parent, Qt::WindowFlags f)
        : QWidget(parent, f)
{
}

GrabberWidget::~GrabberWidget()
{

}

bool GrabberWidget::event(QEvent* event)
{
    if (event->type() == QEvent::Gesture) {
        QGestureEvent *gestureEvent = dynamic_cast< QGestureEvent* >(event);

        Q_FOREACH (QGesture *gesture, gestureEvent->gestures()) {
            gestureEvent->accept(gesture);

            if (gesture->state() == Qt::GestureFinished) {
                
            }
        }
    }

    return QWidget::event(event);
}



TuioInputDevice::TuioInputDevice(QObject* parent)
        : InputDevice(parent)
        , m_screenRect(QApplication::desktop()->rect())
        , m_widget(new GrabberWidget())
{
    m_widget->setHidden(true);
//     m_widget->grabGesture();
}

TuioInputDevice::~TuioInputDevice()
{

}

void TuioInputDevice::addTuioCursor(TUIO::TuioCursor* tcur)
{
    QTouchEvent::TouchPoint touchPoint = tuioCursorToTouchPoint(tcur);

    const QPointF normPos(tcur->getX(), tcur->getY());
    const QPointF screenPos(m_screenRect.width() * normPos.x(), m_screenRect.height() * normPos.y());

    touchPoint.setState(Qt::TouchPointPressed);
    touchPoint.setStartNormalizedPos(normPos);
    touchPoint.setStartPos(touchPoint.pos());
    touchPoint.setStartScreenPos(screenPos);
    touchPoint.setStartScenePos(touchPoint.scenePos());

    touchPoint.setLastNormalizedPos(normPos);
    touchPoint.setLastPos(touchPoint.pos());
    touchPoint.setLastScreenPos(screenPos);
    touchPoint.setLastScenePos(touchPoint.scenePos());

    m_touchPoints[tcur->getSessionID()].append(touchPoint);

    QEvent *touchEvent = new QTouchEvent(QEvent::TouchBegin,
                                         QTouchEvent::TouchScreen,
                                         Qt::NoModifier,
                                         0,
                                         m_touchPoints.value(tcur->getSessionID()));

    QCoreApplication::instance()->postEvent(m_widget, touchEvent);
}

void TuioInputDevice::addTuioObject(TUIO::TuioObject* tobj)
{
    TuioInputPort *port = m_portForSymbol.value(tobj->getSymbolID(), 0);
    if (!port) {
        qDebug() << "Got an add object for an ignored fiducial";
        return;
    }

    FiducialObject fidobj(tobj);
}

void TuioInputDevice::refresh(TUIO::TuioTime ftime)
{
}

void TuioInputDevice::removeTuioCursor(TUIO::TuioCursor* tcur)
{
    QTouchEvent::TouchPoint touchPoint = tuioCursorToTouchPoint(tcur);

    touchPoint.setState(Qt::TouchPointReleased);

    touchPoint.setLastNormalizedPos(m_touchPoints[tcur->getSessionID()].last().normalizedPos());
    touchPoint.setLastPos(m_touchPoints[tcur->getSessionID()].last().pos());
    touchPoint.setLastScreenPos(m_touchPoints[tcur->getSessionID()].last().screenPos());
    touchPoint.setLastScenePos(m_touchPoints[tcur->getSessionID()].last().scenePos());

    QEvent *touchEvent = new QTouchEvent(QEvent::TouchEnd,
                                         QTouchEvent::TouchScreen,
                                         Qt::NoModifier,
                                         0,
                                         m_touchPoints.value(tcur->getSessionID()));

    QCoreApplication::instance()->postEvent(m_widget, touchEvent);

    m_touchPoints.remove(tcur->getSessionID());
}

void TuioInputDevice::removeTuioObject(TUIO::TuioObject* tobj)
{

}

void TuioInputDevice::updateTuioCursor(TUIO::TuioCursor* tcur)
{
    QTouchEvent::TouchPoint touchPoint = tuioCursorToTouchPoint(tcur);

    if (tcur->getMotionSpeed() > 0) {
        touchPoint.setState(Qt::TouchPointMoved);
    } else {
        touchPoint.setState(Qt::TouchPointStationary);
    }

    touchPoint.setLastNormalizedPos(m_touchPoints[tcur->getSessionID()].last().normalizedPos());
    touchPoint.setLastPos(m_touchPoints[tcur->getSessionID()].last().pos());
    touchPoint.setLastScreenPos(m_touchPoints[tcur->getSessionID()].last().screenPos());
    touchPoint.setLastScenePos(m_touchPoints[tcur->getSessionID()].last().scenePos());

    m_touchPoints[tcur->getSessionID()].append(touchPoint);

    QEvent *touchEvent = new QTouchEvent(QEvent::TouchUpdate,
                                         QTouchEvent::TouchScreen,
                                         Qt::NoModifier,
                                         0,
                                         m_touchPoints.value(tcur->getSessionID()));

    QCoreApplication::instance()->postEvent(m_widget, touchEvent);
}

void TuioInputDevice::updateTuioObject(TUIO::TuioObject* tobj)
{

}

QTouchEvent::TouchPoint TuioInputDevice::tuioCursorToTouchPoint(TUIO::TuioCursor* tcur)
{
    const QPointF normPos(tcur->getX(), tcur->getY());
    const QPointF screenPos(m_screenRect.width() * normPos.x(), m_screenRect.height() * normPos.y());

    QTouchEvent::TouchPoint touchPoint(tcur->getSessionID());

    touchPoint.setNormalizedPos(normPos);
    touchPoint.setRect(QRectF());

    touchPoint.setPressure(1.0);
    touchPoint.setScreenRect(m_screenRect);
    touchPoint.setScreenPos(screenPos);

    const QPoint pos((int)screenPos.x() - m_widget->geometry().x(),
                     (int)screenPos.y() - m_widget->geometry().y());

    touchPoint.setPos(pos);
    touchPoint.setSceneRect(QRectF());
    touchPoint.setScenePos(pos);

    return touchPoint;
}


Q_EXPORT_PLUGIN2(ketaroller_tuioinput, TuioInputDevice)
#include "TuioInputDevice.moc"
