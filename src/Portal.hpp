#ifndef PORTAL_H
#define PORTAL_H

#include "Entity.hpp"
#include <cmath>

class Portal : public Entity
{
public:
    Portal(vec2 min, vec2 max, float depth, bool axis = XAXIS, bool dir = POSITIVE);// aligned with x or z axis

    enum axis
    {
        XAXIS = false,
        ZAXIS = true
    };
    enum direction
    {
        POSITIVE = false,
        NEGATIVE = true
    };
    virtual void Draw(const vec3 &camPosition) override;
    void linkPortals(Portal* other);
    float getViewDelta() const;
    vec3 getPosDelta(const vec3 &currPos, float deltaY) const;

    Portal* other;
    vec3 pos;
    bool axis = XAXIS;
    bool dir = POSITIVE;
    bool state = false;
private:
protected:
};

#endif //PORTAL_H