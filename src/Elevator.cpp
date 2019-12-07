#include "Elevator.hpp"


void Elevator::updatePosition()
{
    if(aabb.max.y + speed.y > maxY)
        speed.y=-speed.y;
    else if(aabb.min.y + speed.y < minY)
        speed.y=-speed.y;
    moveEntity(speed);
}