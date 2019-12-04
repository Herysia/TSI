#include "Entity.hpp"

Entity::Entity()
{
    mode = MODE_AABB;
    shaderProgramId = shaderProgramIdColored;
}

void Entity::Draw(const vec3& camPosition)
{
    glUseProgram(shaderProgramId);
        //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shaderProgramId,"rotation_model"),1,false,rotation.pointeur());    PRINT_OPENGL_ERROR();

        glUniform4f(get_uni_loc(shaderProgramId,"rotation_center_model") , rotationCenter.x,rotationCenter.y,rotationCenter.z , 0.0f);                                 PRINT_OPENGL_ERROR();
        glUniform4f(get_uni_loc(shaderProgramId,"translation_model") , translation.x-camPosition.x,translation.y-camPosition.y, translation.z+camPosition.z , 0.0f);                                     PRINT_OPENGL_ERROR();
        if(isColored())
            glUniform3f(get_uni_loc(shaderProgramId,"color_model") , color.x, color.y, color.z);                                     PRINT_OPENGL_ERROR();
    
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();
        if(isTextured())
        {
            glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
            glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();
        }
   
        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();
        if(isTextured())
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
            glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();
        }
    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi);                           PRINT_OPENGL_ERROR();
        if(isTextured())
            glBindTexture(GL_TEXTURE_2D, textureId);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbTriangles, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}


bool Entity::checkCollision(Entity other)
{
    bool ret = false;
    if(mode == MODE_PLANE)
    {
        if(other.mode == MODE_PLANE)
        {
            ret = plane.isColliding(other.plane);
        }
        else
        {
            ret = plane.isColliding(other.aabb);
        }
    }
    else
    {
        if(other.mode == MODE_PLANE)
        {
            ret = other.plane.isColliding(aabb);
        }
        else
        {
            ret = aabb.isColliding(other.aabb);
        }
    }
    return ret;
}