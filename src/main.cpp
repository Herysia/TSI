/*****************************************************************************\
 * TP CPE, 4ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
\*****************************************************************************/


#include "MainWindow.hpp"
#include "glutils.hpp"
#include "global.hpp"

GLuint shaderProgramId;
int main(int argc, char** argv)
{
    MainWindow main = MainWindow();
    main.Init(argc, argv);
    main.Run();
    //Plus rien n'est execute apres cela
    return 0;
}

