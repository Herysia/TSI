#include "Player.hpp"

Player::Player()
{
    rotationCenter = vec3();
    camPosition = vec3();
    speed = vec3();
    size = vec3(0.3f, 1.0f, 0.3f);
    mode = MODE_AABB;
    //Les yeux sont à 90% de la taille du joueur
    aabb = AABB(vec3(-size.x/2, -0.9f*size.y,-size.z/2), vec3(size.x/2, 0.1f*size.y,size.z/2));

}
void Player::updateView()
{
	viewAngle = viewAngle.clamp();
	rotation = mat4::matrice_rotation(viewAngle.x, 1.0f, 0.0f, 0.0f) * mat4::matrice_rotation(viewAngle.y, 0.0f, 1.0f, 0.0f);
}
void Player::Draw()
{
    return;
}

void Player::applyPhysics()
{
    //apply gravity
    speed.y-=0.01;
    //apply speed

    move(speed);
}
void Player::setHorizontalSpeed(vec3 horizontalSpeed)
{
    speed.x = horizontalSpeed.x;
    speed.z = horizontalSpeed.z;
}
void Player::move(float x, float y, float z)
{
    move(vec3(x, y, z));
}

void Player::move(vec3 dist)
{
    camPosition+=dist;
    aabb.max+=dist;
    aabb.min+=dist;
}

vec3 Player::getCamPosition()
{
    return camPosition;
}
vec3 Player::getViewAngle()
{
    return viewAngle;
}
void Player::rotateAngle(float x, float y, float z)
{
    rotateAngle(vec3(x, y, z));
}
void Player::rotateAngle(vec3 angle)
{
    viewAngle+=angle;
}
void Player::handleJump(bool jumpKey)
{
    if(jumpKey && isOnGround)
    {
        speed.y += 0.2f;
        isOnGround=false;
    }
}
void Player::clampViewAngle()
{
    viewAngle = viewAngle.clamp();
}

void Player::applyVerticalCollision(const Entity& other)
{        
    //Vertical collision
    float verticalProj = (other.getPlane().normal.y == 0.0f ? 0.0f : other.getPlane().normal.dot(vec3((aabb.max.x+aabb.min.x)*0.5f, 0.0f, (aabb.max.z+aabb.min.z)*0.5f))+other.getPlane().dist) / other.getPlane().normal.y;
    if(verticalProj<=aabb.min.y || verticalProj>=aabb.max.y)//not vertially colliding (centered)
        return;

    if(!other.getPlane().check2Dcoord(aabb))
        return;
    if(verticalProj-aabb.min.y < aabb.max.y - verticalProj)
        move(0.0f, verticalProj-aabb.min.y, 0.0f);
    else
        move(0.0f, aabb.max.y - verticalProj, 0.0f);
    speed.y = 0.0f;
    isOnGround = true;
}
void Player::applyHorizontalCollision(const Entity& other)
{
    
}
void Player::correctPosition(const Entity& other)
{
    if(other.getMode() == MODE_PLANE)
    {
        if(other.getPlane().collideVertically)
            applyVerticalCollision(other);
        else
            applyHorizontalCollision(other);
    }
    else // AABB-AABB collision
    {
        
    }
    
}