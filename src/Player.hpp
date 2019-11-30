#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"
#include "vec3.hpp"
#include <vector>

class Player: public Entity
{
public:
    Player();
    void updateView();
    void Draw();
    void applyGravity();

    void move(float x, float y, float z);
    void move(vec3 dist);
    vec3 getCamPosition();
    
    void rotateAngle(float x, float y, float z);
    void rotateAngle(vec3 dist);
    vec3 getViewAngle();
    void clampViewAngle();
    void correctPosition(Entity other);
private:
    vec3 viewAngle;
    vec3 camPosition;
    vec3 size;
protected:
};

#endif //PLAYER_H