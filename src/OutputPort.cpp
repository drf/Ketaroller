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

#include "OutputPort_p.h"

#include <QDebug>
#include "OutputDevice.h"

namespace KetaRoller
{

OutputPortFactory::OutputPortFactory(QObject* parent)
        : AbstractPluginFactory(parent)
{

}

OutputPortFactory::~OutputPortFactory()
{

}

OutputPort* OutputPortFactory::newInstance(QObject* parent)
{
    return 0;
}

OutputPort::OutputPort(Port::Type type, QObject *parent)
    : Port(*new OutputPortPrivate(type))
    , QObject(parent)
    , d_ptr(Port::d_ptr)
{

}

OutputPort::~OutputPort()
{

}

void OutputPort::sendToDevice(const QGenericArgument& arg)
{
    Q_D(OutputPort);
    if (!d->device) {
        qWarning() << "Attempting to send a message over a port with no device connected";
        return;
    }
    QMetaObject::invokeMethod(d->device, "newDataFromPort", Q_ARG(KetaRoller::OutputPort*, this), arg);
}

}
