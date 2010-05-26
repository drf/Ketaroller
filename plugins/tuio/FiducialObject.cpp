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
};

FiducialObject::FiducialObject()
{
    d = new Data();
}

FiducialObject::FiducialObject(TUIO::TuioObject* tobj)
{
    d = new Data(tobj);
}

FiducialObject::FiducialObject(const FiducialObject& other)
        : d(other.d)
{
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

