/*****************************************************************************\
 * TP CPE, 4ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
\*****************************************************************************/


#include "MainWindow.hpp"

int main(int argc, char** argv)
{
    MainWindow main = MainWindow(argc, argv);
    main.run();
    //Plus rien n'est execute apres cela
    return 0;
}

