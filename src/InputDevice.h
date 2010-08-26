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

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "AbstractDevice.h"

#include <QVariantMap>

namespace KetaRoller {

class Connection;


class InputPort;

class InputDevicePrivate;
/**
 * \class InputDevice InputDevice.h
 * \brief Base class for input devices
 *
 */
class Q_DECL_EXPORT InputDevice : public AbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(InputDevice)
    Q_DISABLE_COPY(InputDevice)

    Q_PRIVATE_SLOT(d_func(), void removeOutgoingPortDelayed(KetaRoller::InputPort *port, uint mode))

    friend class PluginLoader;

public:
    enum PortRemovalMode {
        KeepPortAliveMode = 0,
        DisconnectOutputsMode = 1,
        DeleteInputPortMode = 2,
        DeleteAllOrphanOutputsMode = 4
    };
    Q_DECLARE_FLAGS(PortRemovalModes, PortRemovalMode)

    InputDevice(QObject *parent = 0);
    virtual ~InputDevice();

    QList< InputPort* > inputPorts() const;

protected:
    bool addOutgoingPort(InputPort *port);
    void removeOutgoingPort(InputPort *port, PortRemovalModes mode = KeepPortAliveMode);

    virtual void init(const QVariantMap &args = QVariantMap());
    virtual bool validatePort(KetaRoller::InputPort *port) = 0;

Q_SIGNALS:
    void portAdded(KetaRoller::InputPort *port);
    void portRemoved(KetaRoller::InputPort *port);
};

}

Q_DECLARE_INTERFACE(KetaRoller::InputDevice, "org.ketamina.InputDevice/0.1")
Q_DECLARE_OPERATORS_FOR_FLAGS(KetaRoller::InputDevice::PortRemovalModes)

#endif // INPUTDEVICE_H
