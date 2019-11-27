/*****************************************************************************\
 * TP CPE, 4ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
\*****************************************************************************/



#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glut.h>

#include "glutils.hpp"

#include "MainWindow.hpp"

int main(int argc, char** argv)
{
    MainWindow main = MainWindow(argc, argv);
    main.run();
    //Plus rien n'est execute apres cela
    return 0;
}

