#ifndef ENTITY_H
#define ENTITY_H
#include "mesh.hpp"
#include "vec3.hpp"
#include "mat4.hpp"
#include "glutils.hpp"
#include "global.hpp"
#include <vector>
#include "Plane.hpp"
#include "AABB.hpp"

enum CollisionMode
{
    MODE_PLANE,
    MODE_AABB
};
class Entity
{
public:
    Entity();
    mat4 rotation;
    vec3 rotationCenter;
    vec3 translation;

    virtual void Draw(const vec3 &camPosition);
    GLuint textureId;
    vec3 color;

    inline CollisionMode getMode() const
    {
        return mode;
    }
    inline Plane getPlane() const
    {
        return plane;
    }
    inline AABB getAABB() const
    {
        return aabb;
    }

private:
    inline bool isColored()
    {
        return shaderProgramId == shaderProgramIdColored;
    }
    inline bool isTextured()
    {
        return shaderProgramId == shaderProgramIdTextured;
    }

protected:
    mesh m;
    int nbTriangles;
    GLuint vbo;
    GLuint vboi;
    bool hasGravity = false;
    bool hasCollisions = false;
    Plane plane;
    AABB aabb;
    CollisionMode mode;
    GLuint shaderProgramId;
};

#endif //ENTITY_H