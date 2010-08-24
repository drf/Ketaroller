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

#ifndef KETAROLLER_INPUTPORT_H
#define KETAROLLER_INPUTPORT_H

#include <Port.h>
#include <OutputPort.h>
#include <QtCore/QList>


namespace KetaRoller {

class OutputPort;


class InputPortPrivate;
class InputPort : public Port
{
    Q_DECLARE_PRIVATE(InputPort)
    Q_DISABLE_COPY(InputPort)
public:
    InputPort(Port::Type type);
    virtual ~InputPort();

    QList< OutputPort* > outputs() const;

    void addOutput(OutputPort *output);

    void disconnectOutput(OutputPort *output, bool destroyOutput = true);
    void setOutputs(const QList< OutputPort* > &output);

    void disconnect(bool destroyOrphanOutputs = true);

    template< typename T > inline void putData(const T &data) {
        foreach (OutputPort *port, outputs()) {
            port->onNewData(data);
        }
    };
};

}

#endif // KETAROLLER_INPUTPORT_H
