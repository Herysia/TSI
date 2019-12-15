#ifndef ROOM4_H
#define ROOM4_H

class Room4
{
public:
    Room4(std::vector<Entity*> &props, std::vector<Portal*> &portals)
    {
        //Room4
        RectangularBlock* block = new RectangularBlock(vec3(-15.0f, -14.0f, -5.0f), vec3(-10.0f, -11.0f, -0.0f), true);
        block->color = vec3(0.5f, 0.5f, 0.5f);
        props.push_back(block);       
        //prevent falling through the portals
        block = new RectangularBlock(vec3(-15.5f, -14.0f, -5.5f), vec3(-10.2f, -11.0f, -0.2f), true);
        block->isInvisible = true;
        props.push_back(block);

        //face1
        Portal* p1 = new Portal(vec2(-14.99f,-13.99f), vec2(-10.01f,-11.01f), -0.03f, Portal::XAXIS, Portal::NEGATIVE);
        Portal* p2 = new Portal(vec2(-0.0f,15.0f), vec2(0.0f,16.5f), -21.0f, Portal::ZAXIS, Portal::POSITIVE);
        p1->linkPortals(p2);
        p1->state = p2->state = true;
        p1->wireframe = p2->wireframe = true;
        portals.push_back(p1);
        portals.push_back(p2);

        //face2
        p1 = new Portal(vec2(-4.99f,-13.99f), vec2(-0.01f,-11.01f), -10.03f, Portal::ZAXIS, Portal::NEGATIVE);
        //p2 = new Portal(vec2(-0.0f,15.0f), vec2(0.0f,16.5f), -21.0f, Portal::ZAXIS, Portal::POSITIVE);
        p1->linkPortals(p2);
        p1->state = p2->state = true;
        portals.push_back(p1);

        

        props.push_back(new Key(vec3(-13.0f, -12.5f,-3.0f), vec3(-12.0f, -11.5f, -2.0f)));
    }
};
#endif //ROOM4_H