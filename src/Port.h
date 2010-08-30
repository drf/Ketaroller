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

#ifndef KETAROLLER_PORT_H
#define KETAROLLER_PORT_H

#include <QtCore/qglobal.h>

namespace KetaRoller {

class AbstractDevice;

class PortPrivate;

/**
 * @brief Base class for a Port
 *
 * This class represents a Port. It is not meant to be used directly: use one of its subclasses instead.
 *
 * Please read @ref routing_model_sec "routing in KetaRoller" to learn more about
 * Ports and Devices.
 */
class Q_DECL_EXPORT Port
{
    Q_DECLARE_PRIVATE(Port)
    Q_DISABLE_COPY(Port)
public:
    /**
     * The type of this port
     */
    enum Type {
        /** An unknown type */
        UnknownType = 0,
        /** A port sending or receiving gesture events */
        GestureType = 1,
        /** A port sending or receiving TUIO messages */
        TUIOType = 2,
        /** A port sending or receiving MIDI messages */
        MIDIType = 3
    };

    /**
     * Base destructor
     */
    virtual ~Port();

    /**
     * @returns The type of this port
     */
    Type type() const;

protected:
    /**
     * Base constructor
     */
    Port(PortPrivate &dd);

    PortPrivate * const d_ptr;
};

}

#endif // KETAROLLER_PORT_H
