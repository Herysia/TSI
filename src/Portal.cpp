#include "Portal.hpp"

Portal::Portal(vec2 min, vec2 max, float depth,  bool axis)
{
    shaderProgramId = shaderProgramIdColored;
    color = vec3(1,0,0);
    mode = MODE_AABB;
    this->axis = axis;
    glUseProgram(shaderProgramId);
    float sommets[3*4];
    if(axis == XAXIS)
    {
        aabb = AABB(vec3(min.x, min.y, depth), vec3(max.x, max.y, depth));
        sommets[3]=aabb.max.x;sommets[4]=aabb.min.y;sommets[5]=depth;
        sommets[6]=aabb.min.x;sommets[7]=aabb.max.y;sommets[8]=depth;
        
    }
    else
    {
        aabb = AABB(vec3(depth, min.y, min.x), vec3(depth, max.y, max.x));
        sommets[3]=depth;sommets[4]=aabb.min.y;sommets[5]=aabb.max.z;
        sommets[6]=depth;sommets[7]=aabb.max.y;sommets[8]=aabb.min.z;
    }
    sommets[0]=aabb.min.x;sommets[1]=aabb.min.y;sommets[2]=aabb.min.z;
    sommets[9]=aabb.max.x;sommets[10]=aabb.max.y;sommets[11]=aabb.max.z;
    pos = aabb.getCenter();
    // float sommets[] = {
    //     0,0,0,
    //     0,0,3,
    //     0,3,3,
    //     0,3,0
    // };
    // //tableau entrelacant coordonnees-normales
    unsigned int index[] = {
        0, 1, 2,
        2, 1, 3
    };
    nbTriangles = 2;
    glGenBuffers(1, &vbo);
    PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STATIC_DRAW);
    PRINT_OPENGL_ERROR();

    glEnableClientState(GL_VERTEX_ARRAY);
    PRINT_OPENGL_ERROR();
    // Indique que le buffer courant (désigné par la variable vbo) est utilisé pour les positions de sommets
    glVertexPointer(3, GL_FLOAT, sizeof(sommets), 0);
    PRINT_OPENGL_ERROR();

    //attribution d'un autre buffer de donnees
    glGenBuffers(1, &vboi);
    PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);
    PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
    PRINT_OPENGL_ERROR();
}

void Portal::Draw(const vec3 &camPosition)
{
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
        glUniform3f(get_uni_loc(shaderProgramId, "min"), aabb.min.x, aabb.min.y, aabb.min.z);
        PRINT_OPENGL_ERROR();
        glUniform3f(get_uni_loc(shaderProgramId, "max"), aabb.max.x, aabb.max.y, aabb.max.z);
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

void Portal::linkPortals(Portal* other)
{
    this->other = other;
    other->other = this;
}