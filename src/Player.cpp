#include "Player.hpp"

Player::Player()
{
    rotationCenter = vec3();
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