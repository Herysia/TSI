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
    this->p1=p1;this->p2=p2;this->p3=p3;this->p4=p4;
    vec3 u = p2 - p1;
    vec3 v = p3 - p1;
    normal = u.cross(v).normalize();
    dist = normal.dot(p1);
}
//TODO reformat + check plan boudaries (2D)
bool Plane::isColliding(AABB other)
{
    /*

        flt------frt        blt = back-left-top
    .' |        .'|            brt = back-right-top
    blt---+--brt  |            brb = back-right-bottom
    |   |     |   |            blb = back-left-bottom
    y |  flb---+--frb        flt = front-left-top
    |.'        | .'  z        frt = front-right-top
    blb------brb            frb = front-right-bottom
    x                    flb = front-left-bottom

    */
    vec3 points[] = {
        vec3(other.min.x, other.min.y, other.min.z),//blb=0
        vec3(other.max.x, other.min.y, other.min.z),//brb=1

        vec3(other.min.x, other.min.y, other.max.z),//flb=2
        vec3(other.max.x, other.min.y, other.max.z),//frb=3

        vec3(other.min.x, other.max.y, other.min.z),//blt=4
        vec3(other.max.x, other.max.y, other.min.z),//brt=5

        vec3(other.min.x, other.max.y, other.max.z),//flt=6
        vec3(other.max.x, other.max.y, other.max.z),//frt=7
    };
    int count = 0;
    for (int i = 0; i<8; i++)
    {
        
    }

/*
    // Convert AABB to center-extents representation
    vec3 c = (other.max + other.min) * 0.5f; // Compute AABB center
    vec3 e = other.max - c; // Compute positive extents

    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    float r = e.x*Abs(normal.x) + e.y*Abs(normal.y) + e.z*Abs(normal.z);

    // Compute distance of box center from plane
    float s = normal.dot(c) - dist;

    // Intersection occurs when distance s falls within [-r,+r] interval
    return Abs(s) <= r;*/
}

bool Plane::isColliding(Plane other)
{
    
}
bool Plane::check2Dcoord(AABB other)
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