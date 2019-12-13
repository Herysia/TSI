#ifndef RECTANGULAR_BLOCK_H
#define RECTANGULAR_BLOCK_H
#include "vec3.hpp"
#include "Entity.hpp"
#include "global.hpp"

class RectangularBlock : public Entity
{
public:
    RectangularBlock(vec3 min, vec3 max, bool shouldBeInside = false);
    virtual void Draw(const vec3 &camPosition) override
    {
        // if(aabb.shouldBeInside)
        //     return;
        glUseProgram(shaderProgramId);
        //envoie des parametres uniformes
        {
            glUniformMatrix4fv(get_uni_loc(shaderProgramId, "rotation_model"), 1, false, rotation.pointeur());
            PRINT_OPENGL_ERROR();

            glUniform4f(get_uni_loc(shaderProgramId, "rotation_center_model"), rotationCenter.x, rotationCenter.y, rotationCenter.z, 0.0f);
            PRINT_OPENGL_ERROR();
            glUniform4f(get_uni_loc(shaderProgramId, "translation_model"), translation.x - camPosition.x, translation.y - camPosition.y, translation.z - camPosition.z, 0.0f);
            PRINT_OPENGL_ERROR();
            glUniform3f(get_uni_loc(shaderProgramId, "color_model"), color.x, color.y, color.z);
            PRINT_OPENGL_ERROR();
            glUniform3f(get_uni_loc(shaderProgramId, "min"), min.x, min.y, min.z);
            PRINT_OPENGL_ERROR();
            glUniform3f(get_uni_loc(shaderProgramId, "max"), max.x, max.y, max.z);
            PRINT_OPENGL_ERROR();
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        PRINT_OPENGL_ERROR();
        PRINT_OPENGL_ERROR();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);

        glDrawElements(GL_TRIANGLES, 3 * nbTriangles, GL_UNSIGNED_INT, 0);
        PRINT_OPENGL_ERROR();
    }
    
private:
protected:
    vec3 min, max;
};

#endif //RECTANGULAR_BLOCK_H