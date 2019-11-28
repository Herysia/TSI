#include "Triangle.hpp"

Triangle::Triangle()
{
    float sommets[]={0.0f,0.0f,0.0f,
    0.8f,0.0f,0.0f,
    0.0f,0.8f,0.0f};

    //attribution d’un buffer de donnees (1 indique la création d’un buffer)
    glGenBuffers(1,&vbo); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(sommets),sommets,GL_STATIC_DRAW);
    PRINT_OPENGL_ERROR();
}

void Triangle::Draw()
{
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo); PRINT_OPENGL_ERROR();
        // Active l’utilisation des données de positions
    glEnableClientState(GL_VERTEX_ARRAY); PRINT_OPENGL_ERROR();
    // Indique que le buffer courant (désigné par la variable vbo) est utilisé pour les posit
    glVertexPointer(3, GL_FLOAT, 0, 0); PRINT_OPENGL_ERROR();
    glDrawArrays(GL_TRIANGLES, 0, 3); PRINT_OPENGL_ERROR();
}