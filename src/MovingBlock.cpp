#include "MovingBlock.hpp"


void MovingBlock::updatePosition()
{
    //vertical
    if(Abs(speed.y) > 0.0001f)
    {
        if(aabb.max.y + speed.y > max.y)
            speed.y=-speed.y;
        else if(aabb.min.y + speed.y < min.y)
            speed.y=-speed.y;
    }


    //horizontal
    if(Abs(speed.x) > 0.0001f)
    {
        if(aabb.max.x + speed.x > max.x)
            speed.x=-speed.x;
        else if(aabb.min.x + speed.x < min.x)
            speed.x=-speed.x;
    }
    if(Abs(speed.z) > 0.0001f)
    {
        if(aabb.max.z + speed.z > max.z)
            speed.z=-speed.z;
        else if(aabb.min.z + speed.z < min.z)
            speed.z=-speed.z;
    }
    moveEntity(speed);
}