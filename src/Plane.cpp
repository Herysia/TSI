#include "Plane.hpp"

Plane::Plane(vec3 normal, float d)
{
    this->normal = normal;
    this->dist = d;
    isInfinite = true;
}
Plane::Plane(vec3 p1, vec3 p2, vec3 p3)
{
    isInfinite = true;
    vec3 u = p2 - p1;
    vec3 v = p3 - p1;
    normal = u.cross(v).normalize();
    dist = normal.dot(p1);
}
Plane::Plane(vec3 p1, vec3 p2, vec3 p3, vec3 p4)
{
    isInfinite = false;
    //todo : 2D min/max
    vec3 u = p2 - p1;
    vec3 v = p3 - p1;
    normal = u.cross(v).normalize();
    dist = normal.dot(p1);
}
//TODO reformat + check plan boudaries (2D)
bool Plane::isColliding(AABB other)
{
    // Convert AABB to center-extents representation
    vec3 c = (other.max + other.min) * 0.5f; // Compute AABB center
    vec3 e = other.max - c; // Compute positive extents

    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    float r = e.x*Abs(normal.x) + e.y*Abs(normal.y) + e.z*Abs(normal.z);

    // Compute distance of box center from plane
    float s = normal.dot(c) - dist;

    // Intersection occurs when distance s falls within [-r,+r] interval
    return Abs(s) <= r;
}

bool Plane::isColliding(Plane other)
{
    
}