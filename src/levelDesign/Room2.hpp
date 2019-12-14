#ifndef ROOM2_H
#define ROOM2_H
#include "../RectangularBlock.hpp"
#include "../Floor.hpp"
#include "../Key.hpp"
#include "../Portal.hpp"

#include "Corridor.hpp"

#include "../Entity.hpp"
class Room2
{
public:
    Room2(std::vector<Entity*> &props, std::vector<Portal*> &portals, Corridor* cIn, Corridor* cOut)
    {
        //Box
        props.push_back(new RectangularBlock(vec3(-10.0f, 11.0f, -6.0f), vec3(-6.0f, 17.5f, 10.0f), true));
        //Path bottom
        props.push_back(new RectangularBlock(vec3(-8.25f, 11.0f, -6.0f), vec3(-7.75f, 12.5f, 10.0f)));
        //stairs
        props.push_back(new RectangularBlock(vec3(-9.25f, 11.0f, -6.0f), vec3(-8.25f, 11.75f, -4.0f)));
        props.push_back(new RectangularBlock(vec3(-7.75f, 11.0f, -6.0f), vec3(-6.75f, 11.75f, -4.0f)));
        //Top path (invisible)
        RectangularBlock* block = new RectangularBlock(vec3(-8.5f, 14.5f, -6.0f), vec3(-7.5f, 15.5f, 10.0f));//larger to be easier
        block->isInvisible = true;
        props.push_back(block);
        //Objective
        props.push_back(new Key(vec3(-8.5f, 16.0f,-5.0f), vec3(-7.5f, 17.0f, -4.0f)));
        //Portals
        Portal* p1 = new Portal(vec2(-8.5f,12.5f), vec2(-7.5f,14.5f), 9.97f, Portal::XAXIS, Portal::NEGATIVE);
        Portal* p2 = new Portal(vec2(-8.5f,15.5f), vec2(-7.5f,17.5f), 9.97f, Portal::XAXIS, Portal::NEGATIVE);
        p1->linkPortals(p2);
        portals.push_back(p1);
        portals.push_back(p2);
    }
};

#endif //ROOM2_H