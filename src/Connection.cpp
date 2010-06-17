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

#include "Connection.h"

#include <QSet>
#include <QTimer>
#include <QDebug>

#include "OutputPort.h"

namespace KetaRoller
{

class Connection::Private
{
public:
    Private() {}

    InputPort *port;
    QList< OutputPort* > outputs;
};

Connection::Connection(InputPort* input, QObject* parent)
        : QObject(parent)
        , d(new Private)
{
    d->port = input;
}

Connection::~Connection()
{
    delete d;
}

bool Connection::disconnectInput()
{
    QList< OutputPort* > allOutputs = d->outputs;

    Q_FOREACH (OutputPort *port, allOutputs) {
        if (!disconnectOutput(port)) {
            return false;
        }
    }

    QTimer::singleShot(0, this, SLOT(deleteLater()));

    return true;
}

bool Connection::disconnectOutput(OutputPort* output)
{
    if (d->outputs.contains(output)) {
        d->outputs.removeOne(output);
        emit outputsChanged(d->outputs);
        return true;
    } else {
        return false;
    }
}

InputPort* Connection::input()
{
    return d->port;
}

QList< OutputPort* > Connection::outputs() const
{
    return d->outputs;
}

bool Connection::setOutputs(const QList< OutputPort* > &outputs)
{
    QSet< OutputPort* > oldOutputs = d->outputs.toSet();
    QSet< OutputPort* > newOutputs = outputs.toSet();

    QSet< OutputPort* > addedOutputs = newOutputs.subtract(oldOutputs);
    QSet< OutputPort* > removedOutputs = oldOutputs.subtract(newOutputs);

    d->outputs = outputs;

    if (!addedOutputs.isEmpty() || !removedOutputs.isEmpty()) {
        emit outputsChanged(outputs);
    }

    return true;
}

bool Connection::addOutput(OutputPort* output)
{
    if (d->outputs.contains(output)) {
        return false;
    }

    d->outputs.append(output);

    return true;
}

template< typename T >
void Connection::putData(const T& data)
{
    foreach (OutputPort *port, d->outputs) {
        port->onNewData(data);
    }
}


}

#include "Connection.moc"
