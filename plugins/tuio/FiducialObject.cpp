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

#include "FiducialObject.h"

#include <TuioObject.h>

#include <QPointF>

class FiducialObject::Data : public QSharedData
{
public:
    Data() {}
    Data(TUIO::TuioObject *tobj)
        : position(tobj->getX(), tobj->getY())
        , xspd(tobj->getXSpeed())
        , yspd(tobj->getYSpeed())
        , motionspd(tobj->getMotionSpeed())
        , motionaccel(tobj->getMotionAccel())
        , rotationspd(tobj->getRotationSpeed())
        , rotationaccel(tobj->getRotationAccel())
        , angle(tobj->getAngle())
        , angledeg(tobj->getAngleDegrees())
        , state(tobj->getTuioState())
        , id(tobj->getSymbolID())
        , tuioObject(tobj)
    {
    }
    Data(const Data& other)
        : position(other.position)
        , xspd(other.xspd)
        , yspd(other.yspd)
        , motionspd(other.motionspd)
        , motionaccel(other.motionaccel)
        , rotationspd(other.rotationspd)
        , rotationaccel(other.rotationaccel)
        , angle(other.angle)
        , angledeg(other.angledeg)
        , state(other.state)
        , id(other.id)
        , event(other.event)
        , tuioObject(other.tuioObject)
    {
    }
    ~Data() {}

    QPointF position;

    float xspd;
    float yspd;

    float motionspd;
    float motionaccel;

    float rotationspd;
    float rotationaccel;

    float angle;
    float angledeg;

    uint state;
    uint id;
    FiducialEvent event;

    TUIO::TuioObject *tuioObject;
};

FiducialObject::FiducialObject()
{
    d = new Data();
    d->event = UnknownEvent;
}

FiducialObject::FiducialObject(TUIO::TuioObject* tobj, FiducialEvent event)
{
    d = new Data(tobj);
    d->event = event;
}

FiducialObject::FiducialObject(const FiducialObject& other)
        : d(other.d)
{
}

FiducialObject& FiducialObject::operator=(const FiducialObject& rhs)
{
    if (this==&rhs) return *this;   //Protect against self-assignment
    d = rhs.d;
    return *this;
}

bool FiducialObject::operator==(const FiducialObject& other) const
{
    return (d->position == other.d->position) && (d->state == other.d->state);
}

FiducialObject::~FiducialObject()
{
}

float FiducialObject::angle() const
{
    return d->angle;
}

float FiducialObject::angleDegrees() const
{
    return d->angledeg;
}

uint FiducialObject::id() const
{
    return d->id;
}

float FiducialObject::motionAcceleration() const
{
    return d->motionaccel;
}

float FiducialObject::motionSpeed() const
{
    return d->motionspd;
}

QPointF FiducialObject::position() const
{
    return d->position;
}

float FiducialObject::rotationAcceleration() const
{
    return d->rotationaccel;
}

float FiducialObject::rotationSpeed() const
{
    return d->rotationspd;
}

float FiducialObject::speedX() const
{
    return d->xspd;
}

float FiducialObject::speedY() const
{
    return d->yspd;
}

uint FiducialObject::state() const
{
    return d->state;
}

FiducialObject::FiducialEvent FiducialObject::event() const
{
    return d->event;
}

TUIO::TuioObject* FiducialObject::tuioObject()
{
    return d->tuioObject;
}
