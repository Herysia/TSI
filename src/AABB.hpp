#ifndef AABB_H
#define AABB_H
#include "Plane.hpp"
class AABB
{
public:
    vec3 min;
    vec3 max;
    
    AABB() : AABB(vec3(), vec3()){};
    AABB(vec3 min, vec3 max);
    bool isColliding(AABB other);
    vec2 getCenter2D();
};

#endif //AABB_H