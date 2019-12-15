#ifndef CORRIDOR_H
#define CORRIDOR_H

class Corridor
{
public:
    Corridor(std::vector<Entity*> &props, std::vector<Portal*> &portals, const vec3 &offset=vec3(), const vec3 &color = vec3(1.0f, 1.0f, 1.0f))
    {
        RectangularBlock* rect = new RectangularBlock(vec3(0.0f, 11.0f, 0.0f)+offset, vec3(3.0f, 13.0f, 3.0f)+offset, true);
        rect->color = color;
        props.push_back(rect);
        rect = new RectangularBlock(vec3(1.5f, 11.0f, 1.5f)+offset, vec3(3.0f, 13.0f, 3.0f)+offset);
        rect->color = color;
        props.push_back(rect);
        this->portals = &portals;
    }
    void setupPx(Portal* px, Portal* pxDest)
    {
        this->px = px;
        this->pxDest = pxDest;
        px->linkPortals(pxDest);
        portals->push_back(px);
        portals->push_back(pxDest);
    }
    void setupPz(Portal* pz, Portal* pzDest)
    {
        this->pz = pz;
        this->pzDest = pzDest;
        pz->linkPortals(pzDest);
        portals->push_back(pz);
        portals->push_back(pzDest);
    }
    void changePortalsState(bool state)
    {
        px->state = state;
        pxDest->state = state;
        pz->state = state;
        pzDest->state = state;
    }
    void changeXState(bool state)
    {
        px->state = state;
        pxDest->state = state;
    }
    void changeZState(bool state)
    {
        pz->state = state;
        pzDest->state = state;
    }
    
private:
    Portal* px;
    Portal* pxDest;
    Portal* pz;
    Portal* pzDest;
    std::vector<Portal*> *portals;

};

#endif //CORRIDOR_H