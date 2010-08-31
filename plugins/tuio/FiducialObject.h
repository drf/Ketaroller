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

#ifndef FIDUCIALOBJECT_H
#define FIDUCIALOBJECT_H

#include <QtCore/QSharedDataPointer>
#include <QtCore/QMetaType>

namespace TUIO {
    class TuioObject;
}

class QPointF;

/**
* @brief The class for Tuio Fiducial messages
*
* This class contains some info about TuioObject messages received by the TuioInputDevice
* thanks to Tuio C++ framework (developed by Martin Kaltenbrunner, MTG).
*
* Our FiducialObjects contain just the relevant info about the fiducials on the Reactable
* and can be routed in Ketaroller system.
*
* @sa TuioInputDevice
*/
class Q_DECL_EXPORT FiducialObject
{
public:

    /**
    * The type of event occurred to this FiducialObject
    */
    enum FiducialEvent {
        UnknownEvent = 0,
        FiducialAddedEvent,
        FiducialRemovedEvent,
        FiducialUpdatedEvent
    };

    /**
    * Empty constructor
    */
    FiducialObject();
    /**
    * Base constructor
    */
    FiducialObject(TUIO::TuioObject *tobj, FiducialEvent event = FiducialUpdatedEvent);
    /**
    * Copy constructor
    */
    FiducialObject(const FiducialObject &other);
    /**
    * Empty destructor
    */
    ~FiducialObject();

    FiducialObject &operator=(const FiducialObject &rhs);
    /**
    * Operator "==" overloading
    */
    bool operator==(const FiducialObject &other) const;

    /**
    * @returns The position of the Fiducial on the table in QPointF coordinates type.
    */
    QPointF position() const;

    /**
    * @returns The speed of the Fiducial on the table X-axis.
    */
    float speedX() const;
    /**
    * @returns The speed of the Fiducial on the table Y-axis.
    */
    float speedY() const;
    /**
    * @returns The motion speed of the Fiducial.
    */
    float motionSpeed() const;
    /**
    * @returns The motion acceleration of the Fiducial.
    */
    float motionAcceleration() const;
    /**
    * @returns The rotation speed of the Fiducial.
    */
    float rotationSpeed() const;
    /**
    * @returns The rotation acceleration of the Fiducial.
    */
    float rotationAcceleration() const;

    /**
    * @returns The rotation angle of the Fiducial.
    */
    float angle() const;
    /**
    * @returns The rotation angle in degrees of the Fiducial.
    */
    float angleDegrees() const;

    /**
    * @returns The state of the Fiducial.
    */
    uint state() const;

    /**
    * @returns The event occurred to the Fiducial, i.e if it has been is added, updated or removed.
    */
    FiducialEvent event() const;

    /**
    * @returns
    */
    TUIO::TuioObject *tuioObject();

private:
    class Data;
    QSharedDataPointer< Data > d;
};

Q_DECLARE_METATYPE(FiducialObject)

#endif // FIDUCIALOBJECT_H
