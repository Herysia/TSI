#ifndef KEY_H
#define KEY_H

#include "RectangularBlock.hpp"
#include "Player.hpp"
#include "levelDesign/Corridor.hpp"
class Player;

class Key : public RectangularBlock
{
public:
    Key(vec3 min, vec3 max, Corridor* cIn = nullptr, Corridor* cOut = nullptr);
    virtual void Draw(const vec3 &camPosition, bool) override;
    bool checkCollision(Player* player);

    static int maxScore;
    Corridor* cIn;
    Corridor* cOut;
private:
    bool hasBeenTaken = false;
protected:
};
#endif //KEY_H
