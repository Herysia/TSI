#ifndef MOVINGBLOCK_H
#define MOVINGBLOCK_H
#include "vec3.hpp"
#include "RectangularBlock.hpp"

class MovingBlock : public RectangularBlock
{
    public:
    MovingBlock(vec3 min, vec3 max) : RectangularBlock(min, max) {}

    virtual void updatePosition() override;
    inline void setVerticalMinMax(float min, float max)
    {
        this->min.y = min;
        this->max.y = max;
    }
    inline void setMinMax(vec3 min, vec3 max)
    {
        this->min = min;
        this->max = max;
    }
    inline void setVerticalSpeed(float speedY)
    {
        speed.y = speedY;
    }
    inline float getVerticalSpeed()
    {
        return speed.y;
    }
    inline vec3 setSpeed(vec3 speed)
    {
        this->speed = speed;
    }
    inline vec3 getSpeed()
    {
        return speed;
    }
    private:
        vec3 max;
        vec3 min;
        vec3 speed;
    protected:
};
#endif // MOVINGBLOCK_H