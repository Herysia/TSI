#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

class Player: public Entity
{
public:
    Player();
    void updateView();
    void Draw();
    vec3 viewAngle;
private:
protected:
};

#endif //PLAYER_H