#ifndef ROOM3_H
#define ROOM3_H

class Room3
{
public:
    Room3(std::vector<Entity*> &props, std::vector<Portal*> &portals)
    {
        float offset = 12.0f;
        Corridor* corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(1.0f, 1.0f, 0.0f));
        Portal* p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 1
        Portal* p2 = new Portal(vec2(0.0f,11.0f + offset + 3.0f), vec2(1.5f,13.0f + offset +3.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);//room3 - 2
        corr->setupPz(p1, p2);
        corr->changeZState(true);

        offset+=3.0f;

        corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(0.5f, 1.0f, 0.0f));
        p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 2
        p2 = new Portal(vec2(0.0f,11.0f + offset+3.0f), vec2(1.5f,13.0f + offset +3.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);//room3 - 3
        corr->setupPz(p1, p2);
        corr->changeZState(true);
        
        offset+=3.0f;

        corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(0.5f, 1.0f, 0.5f));
        p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 3
        p2 = new Portal(vec2(0.0f,11.0f + offset+3.0f), vec2(1.5f,13.0f + offset +3.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);//room3 - 4
        corr->setupPz(p1, p2);
        corr->changeZState(true);
        
        offset+=3.0f;

        corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(0.5f, 1.0f, 1.0f));
        p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 4
        p2 = new Portal(vec2(0.0f,11.0f + offset+3.0f), vec2(1.5f,13.0f + offset +3.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);//room3 - 5
        corr->setupPz(p1, p2);
        corr->changeZState(true);
        
        offset+=3.0f;

        corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(0.0f, 0.5f, 1.0f));
        p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 5
        p2 = new Portal(vec2(0.0f,11.0f + offset+3.0f), vec2(1.5f,13.0f + offset +3.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);//room3 - 6
        corr->setupPz(p1, p2);
        corr->changeZState(true);
        
        offset+=3.0f;

        corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(0.0f, 0.0f, 1.0f));
        p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 6
        p2 = new Portal(vec2(0.0f,11.0f + offset+3.0f), vec2(1.5f,13.0f + offset +3.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);//room3 - 7
        corr->setupPz(p1, p2);
        corr->changeZState(true);
        
        offset+=3.0f;

        corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(0.5f, 0.0f, 0.5f));
        p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 7
        p2 = new Portal(vec2(0.0f,11.0f + offset+3.0f), vec2(1.5f,13.0f + offset +3.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);//room3 - 8
        corr->setupPz(p1, p2);
        corr->changeZState(true);
        
        offset+=3.0f;

        corr = new Corridor(props, portals, vec3(0.0f, offset, 0.0f), vec3(0.5f, 0.5f, 0.5f));
        p1 = new Portal(vec2(0.0f,11.0f + offset), vec2(1.5f,13.0f + offset), 2.97f, Portal::XAXIS, Portal::NEGATIVE);//room3 - 8
        p2 = new Portal(vec2(-13.25f,-14.0f), vec2(-11.75f,-12.0f), -4.97f, Portal::XAXIS, Portal::POSITIVE);//room4
        corr->setupPz(p1, p2);
        corr->changeZState(true);
        
    }
};

#endif //ROOM3_H