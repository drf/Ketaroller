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

#ifndef TUIOINPUTDEVICE_H
#define TUIOINPUTDEVICE_H

#include "InputDevice.h"

#include "TuioListener.h"

#include <QtCore/QThread>
#include <QtCore/QHash>

#include <QtGui/QTouchEvent>
#include <QtGui/QWidget>

class TuioInputPort;

class Q_DECL_EXPORT GrabberWidget : public QWidget
{
    Q_OBJECT
public:
    GrabberWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~GrabberWidget();

    virtual bool event(QEvent* event);
};

class Q_DECL_EXPORT TuioInputDevice : public KetaRoller::InputDevice, public TUIO::TuioListener
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::InputDevice)
    Q_DISABLE_COPY(TuioInputDevice)

public:
    TuioInputDevice(QObject* parent = 0);
    virtual ~TuioInputDevice();

    virtual void addTuioCursor(TUIO::TuioCursor* tcur);
    virtual void addTuioObject(TUIO::TuioObject* tobj);

    virtual void refresh(TUIO::TuioTime ftime);

    virtual void removeTuioCursor(TUIO::TuioCursor* tcur);
    virtual void removeTuioObject(TUIO::TuioObject* tobj);

    virtual void updateTuioCursor(TUIO::TuioCursor* tcur);
    virtual void updateTuioObject(TUIO::TuioObject* tobj);

private:
    QHash< qint64, QList< QTouchEvent::TouchPoint > > m_touchPoints;
    QHash< qint32, TuioInputPort* > m_portForSymbol;
    QHash< Qt::GestureType, TuioInputPort* > m_portForGesture;
    QWidget *m_widget;
    QRect m_screenRect;

    QTouchEvent::TouchPoint tuioCursorToTouchPoint(TUIO::TuioCursor *tcur);
};

#endif // TUIOINPUTDEVICE_H
