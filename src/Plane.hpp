#ifndef PLANE_H
#define PLANE_H
#include "vec2.hpp"
#include "vec3.hpp"
#include "AABB.hpp"
#include "global.hpp"
class AABB;
class Plane
{
public:
    Plane(): Plane(vec3(0.0f, 0.0f, 1.0f), 0.0f){};
    Plane(vec3 normal, float d);
    Plane(vec3 p1, vec3 p2, vec3 p3);
    Plane(vec3 p1, vec3 p2, vec3 p3, vec3 p4);
    vec3 normal;
    vec2 min;
    vec2 max;
    float dist;
    bool isInfinite;
    bool isColliding(AABB other);
    bool isColliding(Plane other);
};

#endif //PLANE_H