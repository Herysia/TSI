#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"
#include "vec3.hpp"
#include "MovingBlock.hpp"
#include "Portal.hpp"
#include <vector>
#include <cmath>

class Player : public Entity
{
public:
    Player();
    void updateView();
    void setPortalView(float angleY);
    void resetPortalView();
    void Draw();
    void applyPhysics();

    void move(float x, float y, float z);
    void move(const vec3 &dist);
    vec3 getCamPosition();

    void rotateAngle(float x, float y, float z);
    void rotateAngle(const vec3 &dist);
    vec3 getViewAngle();
    void clampViewAngle();
    void correctPosition(const Entity &other);
    void setHorizontalSpeed(const vec2 &horizontalSpeed);
    void setVerticalSpeed(float verticalSpeed);
    void handleJump(bool jumpKey);
    
    bool checkPortalCollision(const Portal &portal);
    inline void resetSkippedCollision()
    {
        skipCollision = false;
    }
    bool noClipMode = false;
private:
    vec3 viewAngle;
    vec3 camPosition;
    vec3 size;

    vec3 speed;
    bool isOnGround;

    bool applyVerticalCollision(const Plane &other);
    bool applyVerticalCollision(const AABB &other);
    bool applyHorizontalCollision(const AABB &other);
    bool skipCollision = false;

    inline void resetPosition()
    {
        camPosition = vec3(0.0f, 1.0f, 0.0f);
        aabb = AABB(vec3(-size.x * 0.5f, -0.9f * size.y, -size.z * 0.5f) + camPosition, vec3(size.x * 0.5f, 0.1f * size.y, size.z * 0.5f) + camPosition);
    }


    vec3 AngleVector(const vec3 &viewAngle);
protected:
};

#endif //PLAYER_H