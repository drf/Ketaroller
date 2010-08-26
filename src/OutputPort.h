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

#ifndef KETAROLLER_OUTPUTPORT_H
#define KETAROLLER_OUTPUTPORT_H

#include <Port.h>

#include <QtPlugin>
#include <QDebug>


namespace KetaRoller {

class OutputPortPrivate;
class Q_DECL_EXPORT OutputPort : public Port, public QObject
{
    Q_DECLARE_PRIVATE(OutputPort)
    Q_DISABLE_COPY(OutputPort)

    friend class InputPort;
public:
    OutputPort(Port::Type type);
    virtual ~OutputPort();

    void sendToDevice(const QGenericArgument &arg);

protected:
    PortPrivate * const d_ptr;

    friend class OutputDevice;
};

}

Q_DECLARE_INTERFACE(KetaRoller::OutputPort, "org.ketamina.OutputPortInterface/1.0")

#endif
