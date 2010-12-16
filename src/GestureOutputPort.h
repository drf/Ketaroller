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


#ifndef KETAROLLER_GESTUREOUTPUTPORT_H
#define KETAROLLER_GESTUREOUTPUTPORT_H

#include <OutputPort.h>

class QGesture;

namespace KetaRoller {

class Q_DECL_EXPORT GestureOutputPort : public KetaRoller::OutputPort
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::OutputPort)
    Q_DISABLE_COPY(GestureOutputPort)

public:
    explicit GestureOutputPort(QObject* parent = 0);
    virtual ~GestureOutputPort();

public slots:
    /**
    * This function receives and stores the QGesture messages passed by an input device through the InputPort.
    * It's a compulsory reimplementation of the data receiver callback as explained in
    * @ref generic_argument_model_sec "the generic argument model". Please read
    * @ref creating_output_port_plugin_sec "creating an OutputPort" for a better overview over this method.
    *
    * @param gesture A Gesture passed by the input.
    */
    void receiveData(QGesture *gesture);
};

}

#endif // KETAROLLER_GESTUREOUTPUTPORT_H
