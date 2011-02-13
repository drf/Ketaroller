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


#ifndef BCTOUTPUTDEVICE_H
#define BCTOUTPUTDEVICE_H

#include <KetaRoller/OutputDevice>

#include <midi/MIDIMessage.h>
#include <tuio/FiducialObject.h>

#include <QGesture>
#include <QLineF>

class QTouchEvent;
class QGesture;

namespace KetaRoller {
    class OutputPort;
}

class BctOutputDevice : public KetaRoller::OutputDevice
{
    Q_OBJECT
    Q_DISABLE_COPY(BctOutputDevice)

public:
    explicit BctOutputDevice(QObject* parent = 0);
    virtual ~BctOutputDevice();

    virtual bool validatePort(KetaRoller::OutputPort* port);
    virtual void init(const QVariantMap& args = QVariantMap());

public Q_SLOTS:
    void newDataFromPort(KetaRoller::OutputPort *port, const FiducialObject &obj);
    void newDataFromPort(KetaRoller::OutputPort *port, const MIDIMessage &obj);
    void newDataFromPort(KetaRoller::OutputPort *port, QGesture *gesture);
    void newDataFromPort(KetaRoller::OutputPort *port, QTouchEvent *event);

private:
    QRect m_screenRect;
    QPointF m_center;
    QHash< uint, FiducialObject > m_lastFiducialPos;
    QPointF m_lastHotspot;
    QTime m_swipeDuration;

    void evaluateSwipe(QLineF swipeLine);
};

#endif // BCTOUTPUTDEVICE_H
