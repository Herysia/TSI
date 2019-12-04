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
Plane::Plane(vec3 p1, vec3 p2, vec3 p3, vec3 p4, bool vert)
{
    isInfinite = false;
    this->p1=p1;this->p2=p2;this->p3=p3;this->p4=p4;
    vec3 u = p2 - p1;
    vec3 v = p3 - p1;
    normal = u.cross(v).normalize();
    dist = normal.dot(p1);
    collideVertically = vert;
}

bool Plane::isColliding(const Plane& other) const
{
    
}
bool Plane::check2Dcoord(const AABB& other) const
{
    if(isInfinite)
        return false;
    vec2 center2D = other.getCenter2D();
    /*
    std::cout << "------------------" << std::endl;
    std::cout << (center2D-p1.get2D()).cross((p2-p1).get2D())  << std::endl;
    std::cout << (center2D-p4.get2D()).cross((p3-p4).get2D())  << std::endl;
    std::cout << (center2D-p1.get2D()).cross((p4-p1).get2D())  << std::endl;
    std::cout << (center2D-p2.get2D()).cross((p3-p2).get2D())  << std::endl;
    */

    //if the point is neither between or outside both lines (opposite lines from the plane)
    //  /!\ The plane shape must be convex
    if(!((center2D-p1.get2D()).cross((p2-p1).get2D()) > 0.0f ^ (center2D-p4.get2D()).cross((p3-p4).get2D()) > 0.0f))
        return false;
    //outside axis2
    if(!((center2D-p1.get2D()).cross((p4-p1).get2D()) > 0.0f ^ (center2D-p2.get2D()).cross((p3-p2).get2D()) > 0.0f))
        return false;
    return true;
}