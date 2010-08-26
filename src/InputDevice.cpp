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

#include "InputDevice_p.h"
#include "InputPort.h"

namespace KetaRoller {

InputDevice::InputDevice(QObject* parent)
    : AbstractDevice(*new InputDevicePrivate, parent)
{
}

InputDevice::~InputDevice()
{
}

bool InputDevice::addOutgoingPort(InputPort* port)
{
    Q_D(InputDevice);

    if (d->ports.contains(port)) {
        return false;
    }

    if (validatePort(port)) {
        d->ports.append(port);
        emit portAdded(port);
        return true;
    }

    return false;
}

QList< InputPort* > InputDevice::inputPorts() const
{
    Q_D(const InputDevice);
    return d->ports;
}

void InputDevice::removeOutgoingPort(InputPort* port, PortRemovalModes mode)
{
    Q_D(InputDevice);
    d->ports.removeOne(port);

    emit portRemoved(port);

    QMetaObject::invokeMethod(this, "removeOutgoingPortDelayed", Qt::QueuedConnection,
                              Q_ARG(KetaRoller::InputPort*, port), Q_ARG(uint, (uint)mode));
}

void InputDevicePrivate::removeOutgoingPortDelayed(KetaRoller::InputPort *port, uint mode)
{
    InputDevice::PortRemovalModes pModes = static_cast< InputDevice::PortRemovalModes >(mode);
    if (pModes & InputDevice::DisconnectOutputsMode) {
        port->disconnect(mode & InputDevice::DeleteAllOrphanOutputsMode);
    }

    if (pModes & InputDevice::DeleteInputPortMode) {
        delete port;
    }
}

void InputDevice::init(const QVariantMap& args)
{
    Q_UNUSED(args)
}

}

#include "InputDevice.moc"
