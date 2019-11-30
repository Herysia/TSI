#include "AABB.hpp"

AABB::AABB(vec3 min, vec3 max)
{
    this->min = min;
    this->max = max;
}

bool AABB::isColliding(AABB other)
{

}