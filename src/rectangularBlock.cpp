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
    aabb = AABB(min, max);
    aabb.shouldBeInside = shouldBeInside;
    color = vec3(1.0f, 1.0f, 1.0f);
    //coordonnees geometriques des sommets
    vec3 blb(min.x, min.y, min.z);//blb=0
    vec3 brb(max.x, min.y, min.z);//brb=1

    vec3 flb(min.x, min.y, max.z);//flb=2
    vec3 frb(max.x, min.y, max.z);//frb=3

    vec3 blt(min.x, max.y, min.z);//blt=4
    vec3 brt(max.x, max.y, min.z);//brt=5

    vec3 flt(min.x, max.y, max.z);//flt=6
    vec3 frt(max.x, max.y, max.z); //frt=7


    // //tableau entrelacant coordonnees-normales
    // unsigned int index[]={
    //     /*bottom*/
    //     0,1,2,
    //     1,2,3,
    //     /*back*/
    //     0,1,5,
    //     0,4,5,
    //     /*front*/
    //     2,3,7,
    //     2,6,7,
    //     /*right*/
    //     1,3,7,
    //     1,5,7,
    //     /*left*/
    //     0,2,6,
    //     0,4,6,
    //     /*top*/
    //     4,5,7,
    //     4,6,7
    // };
    vec3 iv3 = vec3();//ignored
    vec2 iv2 = vec2();//ignored

    vertex_opengl v0=vertex_opengl(blb,iv3,iv3,iv2);
    vertex_opengl v1=vertex_opengl(brb,iv3,iv3,iv2);
    vertex_opengl v2=vertex_opengl(flb,iv3,iv3,iv2);
    vertex_opengl v3=vertex_opengl(frb,iv3,iv3,iv2);
    vertex_opengl v4=vertex_opengl(blt,iv3,iv3,iv2);
    vertex_opengl v5=vertex_opengl(brt,iv3,iv3,iv2);
    vertex_opengl v6=vertex_opengl(flt,iv3,iv3,iv2);
    vertex_opengl v7=vertex_opengl(frt,iv3,iv3,iv2);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3,v4,v5,v6,v7};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(1,2,3);
    triangle_index tri2=triangle_index(0,1,5);
    triangle_index tri3=triangle_index(0,4,5);
    triangle_index tri4=triangle_index(2,3,7);
    triangle_index tri5=triangle_index(2,6,7);
    triangle_index tri6=triangle_index(1,3,7);
    triangle_index tri7=triangle_index(1,5,7);
    triangle_index tri8=triangle_index(0,2,6);
    triangle_index tri9=triangle_index(0,4,6);
    triangle_index tri10=triangle_index(4,5,7);
    triangle_index tri11=triangle_index(4,6,7);
    triangle_index index[]={tri0,tri1,tri2,tri3,tri4,tri5,tri6,tri7,tri8,tri9,tri10,tri11};
    nbTriangles = 12;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();
    
}