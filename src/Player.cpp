#include "Player.hpp"

Player::Player()
{
    rotationCenter = vec3();
    camPosition = vec3(0.0f, 1.0f, 0.0f);
    speed = vec3();
    size = vec3(0.1f, 1.0f, 0.1f);
    mode = MODE_AABB;
    //Les yeux sont à 90% de la taille du joueur
    aabb = AABB(vec3(-size.x * 0.5f, -0.9f * size.y, -size.z * 0.5f) + camPosition, vec3(size.x * 0.5f, 0.1f * size.y, size.z * 0.5f) + camPosition);
}
void Player::updateView()
{
    viewAngle = viewAngle.clamp();
    rotation = mat4::matrice_rotation(viewAngle.x, 1.0f, 0.0f, 0.0f) * mat4::matrice_rotation(viewAngle.y, 0.0f, 1.0f, 0.0f);
}
void Player::setPortalView(float angleY)
{
    vec3 angle = viewAngle;
    angle.y+=angleY;
    angle = angle.clamp();
    rotation = mat4::matrice_rotation(angle.x, 1.0f, 0.0f, 0.0f) * mat4::matrice_rotation(angle.y, 0.0f, 1.0f, 0.0f);
}
void Player::resetPortalView()
{
    updateView();
}
void Player::Draw()
{
    return;
}

void Player::applyPhysics()
{
    if(speed.y <= 0.001f)//falling from height
        isOnGround = false;
    //apply gravity
    if(!noClipMode)
        speed.y -= 0.001;
    //apply speed

    move(speed);
}
void Player::setVerticalSpeed(float verticalSpeed)
{
    speed.y = verticalSpeed*0.02;
}
void Player::setHorizontalSpeed(const vec2 &horizontalSpeed)
{
    speed.x = horizontalSpeed.x;
    speed.z = horizontalSpeed.y;
}
void Player::move(float x, float y, float z)
{
    move(vec3(x, y, z));
}

void Player::move(const vec3 &dist)
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
void Player::rotateAngle(const vec3 &angle)
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

bool Player::applyVerticalCollision(const Plane &other)
{
    //Vertical collision
    float verticalProj = (Abs(other.normal.y) <= 0.0001f ? 0.0f : other.normal.dot(vec3(-(aabb.max.x + aabb.min.x) * 0.5f, 0.0f, (aabb.max.z + aabb.min.z) * 0.5f)) + other.dist) / other.normal.y;
    if (verticalProj <= aabb.min.y || verticalProj >= aabb.max.y) //not vertially colliding gravity center
        return false;
    //TODO TOFIX angled surface will trigger this check, but it shouldn't
    // if ((verticalProj > aabb.min.y && verticalProj > aabb.min.y - speed.y)) //too far inside, should not collide
    // //  ||  (verticalProj<aabb.max.y && verticalProj >= aabb.min.y-2*speed.y))
    // {
    //     //std::cout << "Warning: Too far inside" << std::endl;
    //     return false;
    // }

    if (!other.check2Dcoord(aabb))
        return false;
    if (speed.y<=0) {
        move(0.0f, verticalProj - aabb.min.y, 0.0f);
        isOnGround = true;
    }
    else
        move(0.0f, verticalProj - aabb.max.y , 0.0f);
    speed.y = 0.0f;
    return true;
}
bool Player::applyVerticalCollision(const AABB &other)
{
    bool ret=false;
    if ((aabb.min.x <= other.max.x && aabb.max.x >= other.min.x) //overlapping on x axis;
         && (aabb.min.y <= other.max.y && aabb.max.y >= other.min.y)                       //overlapping on y axis;
         && (aabb.min.z <= other.max.z && aabb.max.z >= other.min.z))                     //overlapping on z axis;
    {

        vec3 p1(other.min.x, other.max.y, other.min.z);
        vec3 p2(other.max.x, other.max.y, other.min.z);
        vec3 p3(other.max.x, other.max.y, other.max.z);
        vec3 p4(other.min.x, other.max.y, other.max.z);
        Plane plane = Plane(p1, p2, p3, p4, true);
        ret|=applyVerticalCollision(plane);

        p1.y = other.min.y;
        p2.y = other.min.y,
        p3.y = other.min.y,
        p4.y = other.min.y,
        plane = Plane(p1, p2, p3, p4, true);
        ret|=applyVerticalCollision(plane);
    }
    return ret;
}
bool Player::applyHorizontalCollision(const AABB &other)
{
    if(skipCollision)
        return false;
    if ((!other.shouldBeInside && (aabb.min.x <= other.max.x && aabb.max.x >= other.min.x) //overlapping on x axis;
         && (aabb.min.y+0.003f <= other.max.y && aabb.max.y >= other.min.y)                //overlapping on y axis; +0.003f: hotfix for overlapped objects
         && (aabb.min.z <= other.max.z && aabb.max.z >= other.min.z))                      //overlapping on z axis;
        || (other.shouldBeInside 
        && (aabb.max.x >= other.max.x || aabb.min.x <= other.min.x 
            || aabb.max.z >= other.max.z || aabb.min.z <= other.min.z) 
        && (aabb.min.y <= other.max.y && aabb.max.y >= other.min.y)))
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
            move(0.0f, 0.0f, f + sizeDelta.z );
        }
        else if (Abs(b - min) < 0.001f)
        {
            move(0.0f, 0.0f, -(b + sizeDelta.z));
        }
        else
        {
            return false;
        }
        return true;
    }
    return false;
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
        bool isVerticallyColliding = applyVerticalCollision(other.getAABB());
        if(isVerticallyColliding && Entity::isTypeOf<MovingBlock>(&other))
        {
            MovingBlock* movingBlock = (MovingBlock*)&other;
            vec3 movingBlockSpeed = movingBlock->getSpeed();
            if(movingBlockSpeed.y < 0.0001f)
                speed.y = movingBlockSpeed.y;
            move(vec3(movingBlockSpeed.x, 0, movingBlockSpeed.z));
        }
        if(!isVerticallyColliding || other.getAABB().shouldBeInside) // we cant collide both vertically and horizontally unless we should be outside
            applyHorizontalCollision(other.getAABB());
    }
}

bool Player::checkPortalCollision(const Portal &portal)
{
    AABB other = portal.getAABB();
    if((portal.axis == Portal::XAXIS && (aabb.max.x <= other.max.x && aabb.min.x >= other.min.x) || portal.axis == Portal::ZAXIS && (aabb.min.x <= other.max.x && aabb.max.x >= other.min.x))
    && (portal.axis == Portal::ZAXIS && (aabb.max.z <= other.max.z && aabb.min.z >= other.min.z) || portal.axis == Portal::XAXIS && (aabb.min.z <= other.max.z && aabb.max.z >= other.min.z))
    && (aabb.min.y <= other.max.y && aabb.max.y >= other.min.y))
    {
        skipCollision = true;
        if(portal.axis == Portal::ZAXIS)
        {
            if(camPosition.x - portal.pos.x > 0  ^ camPosition.x-speed.x - portal.pos.x > 0)
            {
                float angleY = portal.getViewDelta();
                move(portal.getPosDelta(camPosition, angleY));
                rotateAngle(0.0f, angleY, 0.0f);
                return true;
            }
        }
        else
        {
            if(camPosition.z - portal.pos.z > 0  ^ camPosition.z-speed.z - portal.pos.z > 0)
            {
                float angleY = portal.getViewDelta();
                move(portal.getPosDelta(camPosition, angleY));
                rotateAngle(0.0f, angleY, 0.0f);
                return true;
            }
        }
    }
    return false;
}

vec3 Player::AngleVector(const vec3 &viewAngle)
{
    vec3 forward;
    float sp = sin(viewAngle.x);
    float cp = cos(viewAngle.x);
    float sy = sin(viewAngle.x);
    float cy = cos(viewAngle.x);

    forward.x = cp*cy;
    forward.y = cp*sy;
    forward.z = -sp;
    return forward.normalize();
}