#ifndef ROOM2_H
#define ROOM2_H

class Room2
{
public:
    Room2(std::vector<Entity*> &props, std::vector<Portal*> &portals, Corridor* cIn, Corridor* cOut)
    {
        //Box
        props.push_back(new RectangularBlock(vec3(-6.0f, 11.0f, -10.0f), vec3(10.0f, 17.7f, -6.0f), true));
        //Path bottom
        props.push_back(new RectangularBlock(vec3(-6.0f, 11.0f, -8.25f), vec3(10.0f, 12.5f, -7.75f)));
        //stairs
        props.push_back(new RectangularBlock(vec3(-6.0f, 11.0f, -9.25f), vec3(-4.0f, 11.75f, -8.25f)));
        props.push_back(new RectangularBlock(vec3(-6.0f, 11.0f, -7.75f), vec3(-4.0f, 11.75f, -6.75f)));
        //Top path (invisible)
        RectangularBlock* block = new RectangularBlock(vec3(-6.0f, 14.5f, -8.5f), vec3(10.0f, 15.5f, -7.5f));//larger to be easier
        block->isInvisible = true;
        props.push_back(block);
        block = new RectangularBlock(vec3(-4.0f, 14.5f, -10.0f), vec3(-2.5f, 15.5f, -7.5f));//larger to be easier
        block->isInvisible = true;
        props.push_back(block);
        //Objective
        props.push_back(new Key(vec3(-5.0f, 16.0f,-8.5f), vec3(-4.0f, 17.0f, -7.5f), cIn, cOut));
        //Portals
        Portal* p1 = new Portal(vec2(-8.5f,12.5f), vec2(-7.5f,14.5f), 9.97f, Portal::ZAXIS, Portal::NEGATIVE);
        Portal* p2 = new Portal(vec2(-8.5f,15.5f), vec2(-7.5f,17.5f), 9.97f, Portal::ZAXIS, Portal::NEGATIVE);
        p1->state = p2->state = true;
        p1->linkPortals(p2);
        portals.push_back(p1);
        portals.push_back(p2);
    }
};

#endif //ROOM2_H