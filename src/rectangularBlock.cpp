#include "rectangularBlock.hpp"

RectangularBlock::RectangularBlock(vec3 min, vec3 max, bool shouldBeInside)
{
    shaderProgramId = shaderProgramIdColored;
    glUseProgram(shaderProgramId);
    /*
        flt------frt        blt = back-left-top
    .' |        .'|            brt = back-right-top
    blt---+--brt  |            brb = back-right-bottom
    |   |     |   |            blb = back-left-bottom
    y |  flb---+--frb        flt = front-left-top
    |.'        | .'  z        frt = front-right-top
    blb------brb            frb = front-right-bottom
    x                    flb = front-left-bottom
    */
    this->min = min;
    this->max = max;
    aabb = AABB(min, max);
    aabb.shouldBeInside = shouldBeInside;
    color = vec3(1.0f, 1.0f, 1.0f);
    //coordonnees geometriques des sommets
    // vec3 blb(min.x, min.y, min.z);//blb=0
    // vec3 brb(max.x, min.y, min.z);//brb=1

    // vec3 flb(min.x, min.y, max.z);//flb=2
    // vec3 frb(max.x, min.y, max.z);//frb=3

    // vec3 blt(min.x, max.y, min.z);//blt=4
    // vec3 brt(max.x, max.y, min.z);//brt=5

    // vec3 flt(min.x, max.y, max.z);//flt=6
    // vec3 frt(max.x, max.y, max.z); //frt=7

    float sommets[] = {
        min.x, min.y, max.z,  //flb=0
        max.x, min.y, max.z,  //frb=1
        max.x, max.y, max.z,  //frt=2
        min.x, max.y, max.z,  //flt=3
        min.x, min.y, min.z,  //blb=4
        max.x, min.y, min.z,  //brb=5
        max.x, max.y, min.z,  //brt=6
        min.x, max.y, min.z}; //blt=7
    // //tableau entrelacant coordonnees-normales
    unsigned int index[] = {

        /*front*/
        0, 1, 2,
        2, 3, 0,
        /*right*/
        1, 5, 6,
        6, 2, 1,
        /*back*/
        7, 6, 5,
        5, 4, 7,
        /*left*/
        4, 0, 3,
        3, 7, 4,
        /*bottom*/
        4, 5, 1,
        1, 0, 4,
        /*top*/
        3, 2, 6,
        6, 7, 3};
    nbTriangles = 12;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
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