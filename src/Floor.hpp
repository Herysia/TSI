#ifndef FLOOR_H
#define FLOOR_H
#include "Entity.hpp"

class Floor : public Entity
{
public:
    Floor(vec3 p0, vec3 p1, vec3 p2, vec3 p4, bool isVisible = false, vec3 color = vec3());
    virtual void Draw(const vec3 &camPosition, bool) override
    {
        if(!isVisible)
            return;
        Entity::Draw(camPosition);
        //glDrawElements(GL_LINE_LOOP, 3*nbTriangles, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3 * nbTriangles, GL_UNSIGNED_INT, 0);
        PRINT_OPENGL_ERROR();
    }
private:
    bool isVisible;
};

#endif //FLOOR_H