#include "Floor.hpp"
#include "global.hpp"

Floor::Floor()
{
    shaderProgramId = shaderProgramIdTextured;
    glUseProgram(shaderProgramId);
        //Creation manuelle du model 2
    mode = MODE_PLANE;
    //coordonnees geometriques des sommets
    vec3 p0=vec3(-25.0f,-0.9f,-25.0f);
    vec3 p1=vec3( 25.0f,-0.9f,-25.0f);
    vec3 p2=vec3( 25.0f,-0.9f, 25.0f);
    vec3 p3=vec3(-25.0f,-0.9f, 25.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    plane = Plane(p0,p1,p2,p3, true);
    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    nbTriangles = 2;

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

    // Chargement de la texture
    loadTexture("../data/grass.tga",&textureId);

}