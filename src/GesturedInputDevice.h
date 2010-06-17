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

#ifndef GESTUREDINPUTDEVICE_H
#define GESTUREDINPUTDEVICE_H

#include "InputDevice.h"

namespace KetaRoller {

class GesturedInputDevicePrivate;
class GesturedInputDevice : public InputDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GesturedInputDevice)
    Q_DISABLE_COPY(GesturedInputDevice)

    Q_PRIVATE_SLOT(d_func(), void onConnectionCreated(KetaRoller::InputPort *port, KetaRoller::Connection *connection))
    Q_PRIVATE_SLOT(d_func(), void onConnectionSevered(KetaRoller::InputPort *port, KetaRoller::Connection *connection))

public:
    GesturedInputDevice(QObject* parent = 0);
    virtual ~GesturedInputDevice();

    virtual void grabGesture(Qt::GestureType type) = 0;
    virtual void ungrabGesture(Qt::GestureType type) = 0;
};

}

#endif // GESTUREDINPUTDEVICE_H
