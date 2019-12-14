#include "Key.hpp"

Key::Key(vec3 min, vec3 max) : RectangularBlock(min, max, false)
{
    color = vec3(1.0f, 0.0f, 0.0f);
    Key::maxScore++;
}

bool Key::checkCollision(Player* player)
{
    if(hasBeenTaken)
        return false;
    AABB aabb = player->getAABB();
    if((aabb.min.x <= max.x && aabb.max.x >= min.x)
    && (aabb.min.y <= max.y && aabb.max.y >= min.y)               
    && (aabb.min.z <= max.z && aabb.max.z >= min.z))
    {
        hasBeenTaken = true;
    }
    return hasBeenTaken;
}
void Key::Draw(const vec3 &camPosition)
{
    if(hasBeenTaken)
        return;
    RectangularBlock::Draw(camPosition);
}

int Key::maxScore = 0;