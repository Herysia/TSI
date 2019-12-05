#include "Player.hpp"

Player::Player()
{
    rotationCenter = vec3();
    camPosition = vec3(0.0f, 0.0f, 0.0f);
    speed = vec3();
    size = vec3(0.3f, 1.0f, 0.3f);
    mode = MODE_AABB;
    //Les yeux sont à 90% de la taille du joueur
    aabb = AABB(vec3(-size.x * 0.5f, -0.9f * size.y, -size.z * 0.5f) + camPosition, vec3(size.x * 0.5f, 0.1f * size.y, size.z * 0.5f) + camPosition);
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
    speed.y -= 0.001;
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
    camPosition += dist;
    aabb.max += dist;
    aabb.min += dist;
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
    viewAngle += angle;
}
void Player::handleJump(bool jumpKey)
{
    if (jumpKey && isOnGround)
    {
        speed.y += 0.05f;
        isOnGround = false;
    }
}
void Player::clampViewAngle()
{
    viewAngle = viewAngle.clamp();
}

void Player::applyVerticalCollision(const Plane &other)
{
    //Vertical collision
    float verticalProj = (other.normal.y == 0.0f ? 0.0f : other.normal.dot(vec3((aabb.max.x + aabb.min.x) * 0.5f, 0.0f, (aabb.max.z + aabb.min.z) * 0.5f)) + other.dist) / other.normal.y;
    if (verticalProj <= aabb.min.y || verticalProj >= aabb.max.y) //not vertially colliding gravity center
        return;

    std::cout << vec3(verticalProj, aabb.min.y, speed.y) << std::endl;
    if ((verticalProj > aabb.min.y && verticalProj <= aabb.min.y - 2 * speed.y)) //too far inside, should not collide
    //  ||  (verticalProj<aabb.max.y && verticalProj >= aabb.min.y-2*speed.y))
    {
        std::cout << "Too far inside" << std::endl;
        return;
    }

    if (!other.check2Dcoord(aabb))
        return;
    if (verticalProj - aabb.min.y < aabb.max.y - verticalProj)
        move(0.0f, verticalProj - aabb.min.y, 0.0f);
    else
        move(0.0f, aabb.max.y - verticalProj, 0.0f);
    speed.y = 0.0f;
    isOnGround = true;
}
void Player::applyVerticalCollision(const AABB &other)
{
    if ((!other.shouldBeInside && (aabb.min.x <= other.max.x && aabb.max.x >= other.min.x) //overlapping on x axis;
         && (aabb.min.y <= other.max.y && aabb.max.y >= other.min.y)                       //overlapping on y axis;
         && (aabb.min.z <= other.max.z && aabb.max.z >= other.min.z)))                     //overlapping on z axis;
    {
        vec3 p1(other.min.x, other.max.y, other.min.z);
        vec3 p2(other.max.x, other.max.y, other.min.z);
        vec3 p3(other.max.x, other.max.y, other.max.z);
        vec3 p4(other.min.x, other.max.y, other.max.z);
        Plane plane = Plane(p1, p2, p3, p4, true);
        applyVerticalCollision(plane);

        p1.y = other.min.y;
        p2.y = other.min.y,
        p3.y = other.min.y,
        p4.y = other.min.y,
        plane = Plane(p1, p2, p3, p4, true);
        applyVerticalCollision(plane);
    }
}
void Player::applyHorizontalCollision(const AABB &other)
{
    if ((!other.shouldBeInside && (aabb.min.x <= other.max.x && aabb.max.x >= other.min.x) //overlapping on x axis;
         && (aabb.min.y <= other.max.y && aabb.max.y >= other.min.y)                       //overlapping on y axis;
         && (aabb.min.z <= other.max.z && aabb.max.z >= other.min.z))                      //overlapping on z axis;
        || (other.shouldBeInside && (aabb.max.x >= other.max.x || aabb.min.x <= other.min.x || aabb.max.z >= other.max.z || aabb.min.z <= other.min.z) && (aabb.min.y <= other.max.y && aabb.max.y >= other.min.y)))
    {
        vec2 coord2D = aabb.getCenter2D();
        //find closest face
        float r = other.max.x - coord2D.x;
        float l = coord2D.x - other.min.x;
        float f = other.max.z - coord2D.y;
        float b = coord2D.y - other.min.z;
        float min = std::min(r, std::min(l, std::min(f, b)));
        vec3 sizeDelta = size * 0.5f * (other.shouldBeInside ? -1.0f : 1.0f);
        if (Abs(r - min) < 0.001f)
        {
            move(r + sizeDelta.x, 0.0f, 0.0f);
        }
        else if (Abs(l - min) < 0.001f)
        {
            move(-(l + sizeDelta.x), 0.0f, 0.0f);
        }
        else if (Abs(f - min) < 0.001f)
        {
            move(0.0f, 0.0f, f + sizeDelta.z);
        }
        else if (Abs(b - min) < 0.001f)
        {
            move(0.0f, 0.0f, -(b + sizeDelta.z));
        }
        else
            std::cout << "Warning: collision error due to precision" << std::endl;
    }
}
void Player::correctPosition(const Entity &other)
{
    //we use AABB-Plane collisions for ground (and oriented surfaces) -> vertical axis
    //in order to have angled floor
    if (other.getMode() == MODE_PLANE)
    {
        applyVerticalCollision(other.getPlane());
    }
    else //We use  AABB-AABB collision for walls and objects (simple)
    {
        applyVerticalCollision(other.getAABB());
        //applyHorizontalCollision(other.getAABB());
    }
}