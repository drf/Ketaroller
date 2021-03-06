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

#include "InputPort.h"

#include "Port_p.h"
#include "OutputPort.h"

namespace KetaRoller
{

class InputPortPrivate : public PortPrivate
{
public:
    InputPortPrivate(Port::Type t) { type = t; }

    QList< OutputPort* > outputPorts;
    QVariantMap args;
};
InputPort::InputPort(Port::Type type, const QVariantMap& args)
        : Port(*new InputPortPrivate(type))
{
    Q_D(InputPort);
    d->args = args;
}

InputPort::~InputPort()
{
    disconnect(false);
}

void InputPort::addOutput(OutputPort* output)
{
    Q_D(InputPort);

    d->outputPorts.append(output);
}

void InputPort::disconnect(bool destroyOrphanOutputs)
{
    Q_D(InputPort);

    if (destroyOrphanOutputs) {
        QList< OutputPort* >::iterator i = d->outputPorts.begin();

        while (i != d->outputPorts.end()) {
            OutputPort *port = *i;

            i = d->outputPorts.erase(i);

            delete port;
        }
    } else {
        d->outputPorts.clear();
    }
}

void InputPort::disconnectOutput(OutputPort* output, bool destroyOutput)
{
    Q_D(InputPort);

    d->outputPorts.removeOne(output);

    if (destroyOutput) {
        delete output;
    }
}

QList< OutputPort* > InputPort::outputs() const
{
    Q_D(const InputPort);

    return d->outputPorts;
}

void InputPort::setOutputs(const QList< OutputPort* >& output)
{
    Q_D(InputPort);

    d->outputPorts = output;
}

QVariantMap InputPort::args() const
{
    Q_D(const InputPort);
    return d->args;
}

void InputPort::putData(const QGenericArgument& argument)
{
    Q_D(InputPort);
    foreach (OutputPort *port, d->outputPorts) {
        QMetaObject::invokeMethod(port, "receiveData", argument);
    }
}

}
