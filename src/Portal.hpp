#ifndef PORTAL_H
#define PORTAL_H

#include "Entity.hpp"

class Portal : public Entity
{
public:
    Portal(vec2 min, vec2 max, float depth, bool axis = XAXIS);// aligned with x or z axis

    enum axis
    {
        XAXIS = false,
        ZAXIS = true
    };
    virtual void Draw(const vec3 &camPosition) override;
    bool axis = XAXIS;
    void linkPortals(Portal* other);

    Portal* other;
    vec3 pos;
private:
protected:

};

#endif //PORTAL_H