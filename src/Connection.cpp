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

namespace KetaRoller
{

class Connection::Private
{
public:
    Private() : valid(false) {}

    InputPort *port;
    QList< OutputPort* > outputs;
    bool valid;
};

Connection::Connection(InputPort* input, QObject* parent)
        : QObject(parent)
        , d(new Private)
{
    d->port = input;
}

Connection::~Connection()
{
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
    if (!isValid()) {
        return false;
    }

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
    if (!isValid()) {
        return 0;
    }

    return d->port;
}

bool Connection::isValid() const
{
    return d->valid;
}

QList< OutputPort* > Connection::outputs() const
{
    if (!isValid()) {
        return QList< OutputPort* >();
    }

    return d->outputs;
}

void Connection::setIsValid(bool validity)
{
    d->valid = validity;
}

bool Connection::setOutputs(const QList< OutputPort* > &outputs)
{
    if (!isValid()) {
        return false;
    }

    QSet< OutputPort* > oldOutputs = d->outputs.toSet();
    QSet< OutputPort* > newOutputs = outputs.toSet();

    QSet< OutputPort* > addedOutputs = newOutputs.subtract(oldOutputs);
    QSet< OutputPort* > removedOutputs = oldOutputs.subtract(newOutputs);

    Q_FOREACH (OutputPort *port, addedOutputs) {
        if (!validateAddOutput(port)) {
            return false;
        }
    }

    d->outputs = outputs;

    if (!addedOutputs.isEmpty() || !removedOutputs.isEmpty()) {
        emit outputsChanged(outputs);
    }

    return true;
}

bool Connection::addOutput(OutputPort* output)
{
    if (!isValid()) {
        return false;
    }

    if (d->outputs.contains(output)) {
        return false;
    }

    if (!validateAddOutput(output)) {
        return false;
    }

    d->outputs.append(output);

    return true;
}


}

#include "Connection.moc"
