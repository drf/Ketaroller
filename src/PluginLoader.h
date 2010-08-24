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

#ifndef KETAROLLER_PLUGINLOADER_H
#define KETAROLLER_PLUGINLOADER_H

#include <QObject>


namespace KetaRoller {

class InputDevice;


class OutputPort;


class PluginLoader : public QObject
{
public:
    enum Type {
        MIDIType,
        TuioType
    };

    static PluginLoader *instance();

    OutputPort *loadOutputPort(Type type);
    InputDevice *loadInputDevice(Type type);

    virtual ~PluginLoader();

private:
    PluginLoader(QObject* parent = 0);

    class Private;
    Private * const d;
};

}

#endif // KETAROLLER_PLUGINLOADER_H
