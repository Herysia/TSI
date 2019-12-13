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
    void DrawPortals(const vec3 &camPosition, const std::vector<Entity*> &props, int recursionLevel = 0);
    void linkPortals(Portal* other);
    mat4 const clippedProjMat(mat4 const &rotation, mat4 const &projMat) const;

    Portal* other;
    vec3 pos;
    bool axis = XAXIS;
private:
protected:

};

#endif //PORTAL_H