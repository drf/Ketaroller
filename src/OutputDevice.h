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

#ifndef KETAROLLER_OUTPUTDEVICE_H
#define KETAROLLER_OUTPUTDEVICE_H

#include <AbstractDevice.h>
#include <QVariantMap>


namespace KetaRoller {

class OutputPort;

class OutputDevicePrivate;
class Q_DECL_EXPORT OutputDevice : public KetaRoller::AbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(OutputDevice)
    Q_DISABLE_COPY(OutputDevice)

    friend class PluginLoader;

public:
    OutputDevice(QObject *parent = 0);
    virtual ~OutputDevice();

    QList< OutputPort* > outputPorts() const;

    bool addIncomingPort(OutputPort *port);
    void removeIncomingPort(OutputPort *port);

protected:
    virtual void init(const QVariantMap &args = QVariantMap());
    virtual bool validatePort(KetaRoller::OutputPort *port) = 0;

Q_SIGNALS:
    void portAdded(KetaRoller::OutputPort *port);
    void portRemoved(KetaRoller::OutputPort *port);
};

}

#endif // KETAROLLER_OUTPUTDEVICE_H
