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

class QUdpSocket;
class QTcpSocket;
class QHostAddress;
class QTouchEvent;
class QGesture;

namespace KetaRoller {
    class OutputPort;
}

class ModelDescription {
public:
    QString name;
    QHash< int, QString > parameters;
};

class BctOutputDevice : public KetaRoller::OutputDevice
{
    Q_OBJECT
    Q_DISABLE_COPY(BctOutputDevice)

public:
    class Mapping {
    public:
        int tree;
        int param;
        int paramOnAngle;
        int paramOnPosition;
    };

    explicit BctOutputDevice(QObject* parent = 0);
    virtual ~BctOutputDevice();

    virtual bool validatePort(KetaRoller::OutputPort* port);
    virtual void init(const QVariantMap& args = QVariantMap());

    void startConnection(const QHostAddress &address, int port = 6984);
    QHash< int, ModelDescription > models() const;

    bool loadModels(QList< int > id);
    bool startPlaying();

    void mapMidiCC(quint16 ccName, int tree, int param);
    void mapFiducial(quint16 fiducialId, int tree, int paramAngle = -1, int paramPosition = -1);
    void mapMidiNoteOnOff(int tree);

    void unmapMidiCC(quint16 ccName);
    void unmapFiducial(quint16 fiducialId);

public Q_SLOTS:
    void newDataFromPort(KetaRoller::OutputPort *port, const FiducialObject &obj);
    void newDataFromPort(KetaRoller::OutputPort *port, const MIDIMessage &obj);
    void newDataFromPort(KetaRoller::OutputPort *port, QGesture *gesture);
    void newDataFromPort(KetaRoller::OutputPort *port, QTouchEvent *event);

private Q_SLOTS:
    void processNoteOffStack();

Q_SIGNALS:
    void connectionEstabilished();
    void connectionDropped();

private:
    qint64 m_udpTimestamp;
    QRect m_screenRect;
    QPointF m_center;
    QHash< uint, FiducialObject > m_lastFiducialPos;
    QPointF m_lastHotspot;
    QTime m_swipeDuration;
    QHash< int, ModelDescription > m_models;
    QWeakPointer< QTcpSocket > m_tcpSocket;
    QWeakPointer< QUdpSocket > m_udpSocket;
    QList< int > m_loadedModels;
    int m_midiOnOffTree;
    QList< int > m_noteOffStack;

    QHash< int, Mapping > m_midiMappings;
    QHash< int, Mapping > m_fiducialMappings;

    void evaluateSwipe(QLineF swipeLine);
    void sendUdpMessage(int tree, int control, double value);
};

#endif // BCTOUTPUTDEVICE_H
