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

#include "GesturedInputDevice.h"

#include "InputDevice_p.h"

namespace KetaRoller {

class GesturedInputDevicePrivate : public InputDevicePrivate
{
public:
    QHash< Qt::GestureType, qint16 > gestureCount;

    // Q_PRIVATE_SLOTS
    void onConnectionCreated(KetaRoller::InputPort *port, KetaRoller::Connection *connection);
    void onConnectionSevered(KetaRoller::InputPort *port, KetaRoller::Connection *connection);
};

void GesturedInputDevice::grabGesture(Qt::GestureType type)
{

}

void GesturedInputDevicePrivate::onConnectionCreated(KetaRoller::InputPort *port, KetaRoller::Connection *connection)
{

}

void GesturedInputDevicePrivate::onConnectionSevered(KetaRoller::InputPort *port, KetaRoller::Connection *connection)
{

}

GesturedInputDevice::GesturedInputDevice(QObject* parent): InputDevice(parent)
{

}

GesturedInputDevice::~GesturedInputDevice()
{

}

};

#include "GesturedInputDevice.moc"
