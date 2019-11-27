#include "Entity.hpp"

Entity::Entity()
{
    
}

void Entity::Draw()
{
        //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shaderProgramId,"rotation_model"),1,false,rotation.pointeur());    PRINT_OPENGL_ERROR();

        glUniform4f(get_uni_loc(shaderProgramId,"rotation_center_model") , rotationCenter.x,rotationCenter.y,rotationCenter.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        glUniform4f(get_uni_loc(shaderProgramId,"translation_model") , translation.x,translation.y,translation.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, textureId);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbTriangles, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}