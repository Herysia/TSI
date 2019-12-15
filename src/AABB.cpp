#include "AABB.hpp"

AABB::AABB(vec3 min, vec3 max)
{
    this->min = min;
    this->max = max;
}


vec2 AABB::getCenter2D() const
{
    return vec2((max.x + min.x) * 0.5f, (max.z + min.z) * 0.5f);
}
vec3 AABB::getCenter() const
{
    return vec3((max.x + min.x) * 0.5f, (max.y + min.y) * 0.5f, (max.z + min.z) * 0.5f);
}
vec2 AABB::getSize() const
{
    return vec2((max.x - min.x) * 0.5f, (max.z - min.z) * 0.5f);
}