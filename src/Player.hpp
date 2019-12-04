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
    void applyPhysics();

    void move(float x, float y, float z);
    void move(vec3 dist);
    vec3 getCamPosition();
    
    void rotateAngle(float x, float y, float z);
    void rotateAngle(vec3 dist);
    vec3 getViewAngle();
    void clampViewAngle();
    void correctPosition(Entity other);
    void setHorizontalSpeed(vec3 horizontalSpeed);
    void handleJump(bool jumpKey);
private:
    vec3 viewAngle;
    vec3 camPosition;
    vec3 size;

    vec3 speed;
    bool isOnGround;
protected:
};

#endif //PLAYER_H