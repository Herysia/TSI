#ifndef ROOM1_H
#define ROOM1_H
#include "../RectangularBlock.hpp"
#include "../Floor.hpp"
#include "../Key.hpp"
#include "../MovingBlock.hpp"
#include "Corridor.hpp"

#include "../Entity.hpp"

class Room1
{
public:
    Room1(std::vector<Entity*> &props, Corridor* cIn, Corridor* cOut)
    {
        //Box
        props.push_back(new RectangularBlock(vec3(-10.0f, 0.0f, -10.0f), vec3(10.0f, 10.0f, 10.0f), true));

        //big stairs
        //props.push_back(new RectangularBlock(vec3(2.5, 0.0f, -8.5), vec3(2.5f, 0.7f, -5.5)));//overlapping
        props.push_back(new RectangularBlock(vec3(5.5f, 0.0f, -8.5), vec3(8.5, 0.7f, -5.5)));
        props.push_back(new RectangularBlock(vec3(5.5, 0.7f, -5.5), vec3(8.5, 1.4f, -1.83)));
        props.push_back(new RectangularBlock(vec3(5.5, 1.4f, -1.83), vec3(8.5, 2.2f, 1.83)));
        props.push_back(new RectangularBlock(vec3(5.5, 2.1f, 1.83), vec3(8.5, 3.0f, 5.5)));
        props.push_back(new RectangularBlock(vec3(5.5, 3.0f, 5.5), vec3(8.5, 3.8f, 8.5)));

        //small jumps
        props.push_back(new RectangularBlock(vec3(3.5, 3.4f, 5.5), vec3(4.5, 3.8f, 8.5)));
        props.push_back(new RectangularBlock(vec3(1.5, 3.4f, 5.5), vec3(2.5, 3.8f, 8.5)));
        props.push_back(new RectangularBlock(vec3(-0.5, 3.4f, 5.5), vec3(0.5, 3.8f, 8.5)));
        props.push_back(new RectangularBlock(vec3(-2.5, 3.4f, 5.5), vec3(-1.5, 3.8f, 8.5)));
        props.push_back(new RectangularBlock(vec3(-4.5, 3.4f, 5.5), vec3(-3.5, 3.8f, 8.5)));
        
        //tiny path
        props.push_back(new RectangularBlock(vec3(-8.5, 3.4f, 5.5), vec3(-5.5, 3.8f, 8.5)));
        props.push_back(new RectangularBlock(vec3(-7.2, 3.4f, -5.5), vec3(-6.8, 3.8f, 5.5)));
        props.push_back(new RectangularBlock(vec3(-8.5, 3.4f, -8.5), vec3(-5.5, 3.8f, -5.5)));
        
        //autostairs
        props.push_back(new RectangularBlock(vec3(-5.5, 3.4f, -8.5), vec3(-4.5, 3.8f, -5.5)));
        props.push_back(new RectangularBlock(vec3(-4.5, 3.8f, -8.5), vec3(-3.5, 3.9f, -5.5)));
        props.push_back(new RectangularBlock(vec3(-3.5, 3.9f, -8.5), vec3(-2.5, 4.0f, -5.5)));
        props.push_back(new RectangularBlock(vec3(-2.5, 4.0f, -8.5), vec3(-1.5, 4.1f, -5.5)));
        props.push_back(new RectangularBlock(vec3(-1.5, 4.1f, -8.5), vec3(-0.5, 4.2f, -5.5)));
        props.push_back(new RectangularBlock(vec3(-0.5, 4.2f, -8.5), vec3(0.5, 4.3f, -5.5)));
        props.push_back(new RectangularBlock(vec3(0.5, 4.3f, -8.5), vec3(1.5, 4.4f, -5.5)));
        props.push_back(new RectangularBlock(vec3(1.5, 4.4f, -8.5), vec3(2.5, 4.5f, -5.5)));
        props.push_back(new RectangularBlock(vec3(2.5, 4.5f, -8.5), vec3(3.5, 4.6f, -5.5)));
        props.push_back(new RectangularBlock(vec3(3.5, 4.6f, -8.5), vec3(4.5, 4.7f, -5.5)));
        props.push_back(new RectangularBlock(vec3(4.5, 4.7f, -8.5), vec3(5.5, 4.8f, -5.5)));
        props.push_back(new RectangularBlock(vec3(5.5, 4.8f, -8.5), vec3(8.5, 4.9f, -5.5)));
        //plane for the slope
        props.push_back(new Floor(vec3(-5.6, 3.8f, -8.5), vec3(5.5, 4.92f, -8.5), vec3(5.5, 4.92f, -5.5), vec3(-5.6, 3.8f, -5.5)));

        //Vertical movingBlock
        MovingBlock* elevator = new MovingBlock(vec3(1, 0.0f, 0), vec3(4, 0.1f, 3));
        elevator->setVerticalMinMax(0, 4.9);
        elevator->setVerticalSpeed(0.01f);
        props.push_back(elevator);
        //Horizontal moving block
        MovingBlock* horizontal = new MovingBlock(vec3(5.5, 4.8f, -5.5), vec3(8.5, 4.9f, -2.5));
        horizontal->setMinMax(vec3(5.5, 4.8f, -5.5), vec3(8.5, 8.9f, 5.5));
        horizontal->setSpeed(vec3(0,0.005,0.01f));
        props.push_back(horizontal);

        //Objective
        props.push_back(new Key(vec3(6.5, 8.9f, 3.5), vec3(7.5, 9.9f, 4.5)));
        in = cIn;
        out = cOut;
    }
    Corridor* in;
    Corridor* out;
};

#endif //ROOM1_H