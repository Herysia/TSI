#ifndef SPAWN_H
#define SPAWN_H

#include "../Portal.hpp"
#include "../RectangularBlock.hpp"

#include "../Entity.hpp"
class Spawn
{
public:
    Spawn(std::vector<Entity*> &props)
    {
        props.push_back(new RectangularBlock(vec3(-10.0f, 11.0f, -10.0f), vec3(-7.0f, 13.0f, -7.0f), true));
    }
};

#endif //SPAWN_H