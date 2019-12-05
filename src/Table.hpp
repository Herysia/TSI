#ifndef TABLE_H
#define TABLE_H
#include "vec3.hpp"
#include "Entity.hpp"
#include "global.hpp"

class Table : public Entity
{
public:
    Table() : Table(1.0f, 1.0f, 1.0f) {}
    Table(float scalex, float scaley, float scalez);

private:
protected:
};

#endif //TABLE_H