/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include "OutputDevice.h"
#include "AbstractDevice_p.h"
#include "OutputPort.h"
#include "OutputPort_p.h"

namespace KetaRoller
{
class OutputDevicePrivate : public AbstractDevicePrivate
{
public:
    QList< OutputPort* > ports;
};

OutputDeviceFactory::OutputDeviceFactory(QObject* parent)
        : AbstractPluginFactory(parent)
{

}

OutputDeviceFactory::~OutputDeviceFactory()
{

}

OutputDevice::OutputDevice(QObject* parent)
        : AbstractDevice(*new OutputDevicePrivate, parent)
{
}

OutputDevice::~OutputDevice()
{
}

bool OutputDevice::addIncomingPort(OutputPort* port)
{
    Q_D(OutputDevice);

    if (d->ports.contains(port)) {
        return false;
    }

    if (validatePort(port)) {
        d->ports.append(port);
        emit portAdded(port);

        // Set the device onto the port
        port->d_func()->device = this;

        return true;
    }

    return false;
}

QList< OutputPort* > OutputDevice::outputPorts() const
{
    Q_D(const OutputDevice);
    return d->ports;
}

void OutputDevice::removeIncomingPort(OutputPort* port)
{
    Q_D(OutputDevice);
    d->ports.removeOne(port);

    // Remove the device from the port
    port->d_func()->device = 0;

    emit portRemoved(port);
}

}

#include "OutputDevice.moc"
