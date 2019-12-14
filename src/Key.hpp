#ifndef KEY_H
#define KEY_H

#include "rectangularBlock.hpp"
#include "Player.hpp"
class Player;

class Key : public RectangularBlock
{
public:
    Key(vec3 min, vec3 max);
    virtual void Draw(const vec3 &camPosition) override;
    bool checkCollision(Player* player);

    static int maxScore;
private:
    bool hasBeenTaken = false;
protected:
};
#endif //KEY_H