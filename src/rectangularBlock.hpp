#ifndef RECTANGULAR_BLOCK_H
#define RECTANGULAR_BLOCK_H
#include "vec3.hpp"
#include "Entity.hpp"
#include "global.hpp"

class RectangularBlock: public Entity
{
public:
    RectangularBlock(vec3 min, vec3 max, bool shouldBeInside = false);
    virtual void Draw(const vec3& camPosition) override
    {
        Entity::Draw(camPosition);
        glDrawElements(GL_LINE_LOOP, 3*nbTriangles, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
        //glDrawElements(GL_TRIANGLES, 3*nbTriangles, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
private:

protected:

};

#endif //RECTANGULAR_BLOCK_H