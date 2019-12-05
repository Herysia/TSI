#ifndef FLOOR_H
#define FLOOR_H
#include "Entity.hpp"

class Floor : public Entity
{
public:
    Floor();
    virtual void Draw(const vec3 &camPosition) override
    {
        Entity::Draw(camPosition);
        //glDrawElements(GL_LINE_LOOP, 3*nbTriangles, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3 * nbTriangles, GL_UNSIGNED_INT, 0);
        PRINT_OPENGL_ERROR();
    }
};

#endif //FLOOR_H