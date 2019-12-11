#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "vec3.hpp"
#include "RectangularBlock.hpp"

class Elevator : public RectangularBlock
{
    public:
    Elevator(vec3 min, vec3 max) : RectangularBlock(min, max) {}

    virtual void updatePosition() override;
    inline void setMinMax(float min, float max)
    {
        minY = min;
        maxY = max;
    }
    inline void setSpeed(float speedY)
    {
        speed.y = speedY;
    }
    inline float getSpeed()
    {
        return speed.y;
    }
    private:
        float maxY;
        float minY;
    protected:
};
#endif // ELEVATOR_H