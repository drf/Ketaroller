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
#include "AbstractPluginFactory.h"

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

class Q_DECL_EXPORT OutputDeviceFactory : public AbstractPluginFactory
{
    Q_OBJECT
public:
    OutputDeviceFactory(QObject* parent = 0);
    virtual ~OutputDeviceFactory();

    virtual OutputDevice *newInstance(QObject *parent) = 0;
};

}

Q_DECLARE_INTERFACE(KetaRoller::OutputDevice, "org.ketamina.OutputDevice/0.1")
Q_DECLARE_INTERFACE(KetaRoller::OutputDeviceFactory, "org.ketamina.OutputDeviceFactory/0.1")

#define KETAROLLER_OUTPUT_DEVICE_PLUGIN_FACTORY(type, _gen) class Q_DECL_EXPORT _gen##Factory : public KetaRoller::OutputDeviceFactory \
{ \
    Q_OBJECT \
    Q_INTERFACES(KetaRoller::OutputDeviceFactory) \
    Q_DISABLE_COPY(_gen) \
public: \
    _genFactory(QObject* parent = 0) : KetaRoller::OutputDeviceFactory(parent) {} \
    virtual ~_gen##Factory() {} \
    virtual KetaRoller::OutputDevice* newInstance(QObject* parent) { return new _gen(parent); } \
};

#endif // KETAROLLER_OUTPUTDEVICE_H
