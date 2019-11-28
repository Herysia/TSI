#include "MainWindow.hpp"

MainWindow::MainWindow()
{
    camPosition = vec3();
}
MainWindow* MainWindow::currentWindow = NULL;
void MainWindow::Init(int argc, char** argv)
{
    currentWindow=this;
    //**********************************************//
    //Lancement des fonctions principales de GLUT
    //**********************************************//

    //necesssaire sur certains pc
    glewExperimental = GL_TRUE;

    //initialisation
    glutInit(&argc, argv);

    //Mode d'affichage (couleur, gestion de profondeur, ...)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Taille de la fenetre a l'ouverture
    glutInitWindowSize(1366, 768);

    //Titre de la fenetre
    glutCreateWindow("OpenGL");

    //Fonction de la boucle d'affichage
    glutDisplayFunc(displayCallback);


    //inputs
    glutKeyboardFunc(keyboardCallbackDown);
    glutKeyboardUpFunc(keyboardCallbackUp);

    glutSpecialFunc(specialCallbackDown);
    glutSpecialUpFunc(specialCallbackUp);

	//glutPassiveMotionFunc(mouseCallback);
    


    glutTimerFunc(25, timerCallback, 0);

    //Initialisation des fonctions OpenGL
    glewInit();

    //Notre fonction d'initialisation des donnees et chargement des shaders
    loadData();

    //Cursor and keyboard setup
	glutSetCursor(GLUT_CURSOR_NONE);
    glutIgnoreKeyRepeat(1);
}
void MainWindow::displayCallback()
{    
    
    //effacement des couleurs du fond d'ecran
    glClearColor(0.5f, 0.6f, 0.9f, 1.0f);                 PRINT_OPENGL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   PRINT_OPENGL_ERROR();

    // Affecte les parametres uniformes de la vue (identique pour tous les modeles de la scene)
    {
        //envoie de la rotation
        glUniformMatrix4fv(get_uni_loc(shaderProgramId,"rotation_view"),1,false, currentWindow->localPlayer->rotation.pointeur()); PRINT_OPENGL_ERROR();

        //envoie du centre de rotation
        vec3 cv = currentWindow->localPlayer->rotationCenter;
        glUniform4f(get_uni_loc(shaderProgramId,"rotation_center_view") , cv.x,cv.y,cv.z , 0.0f); PRINT_OPENGL_ERROR();

        //envoie de la translation
        vec3 tv = currentWindow->localPlayer->translation;
        glUniform4f(get_uni_loc(shaderProgramId,"translation_view") , tv.x,tv.y,tv.z , 0.0f); PRINT_OPENGL_ERROR();
    }
    
    std::list<Entity>::iterator it;

    for(it = currentWindow->props.begin(); it != currentWindow->props.end(); ++it){
        it->Draw(currentWindow->camPosition);
    }
    //Changement de buffer d'affichage pour eviter un effet de scintillement
    glutSwapBuffers();
}
void MainWindow::keyboardCallback(unsigned char key, int, int, bool down)
{    
    switch (key)
    {
    case 27://escape
        exit(0);
        break;
    case 'z':
        currentWindow->keyState.forward = down;
        break;
    case 's':
        currentWindow->keyState.backward = down;
        break;
    case 'q':
        currentWindow->keyState.left = down;
        break;
    case 'd':
        currentWindow->keyState.right = down;
        break;
    }
}

void MainWindow::specialCallback(int key, int ,int, bool down)
{
    float dL=0.03f;
    switch (key)
    {
    case GLUT_KEY_UP:
        currentWindow->keyState.view.up = down;
        break;
    case GLUT_KEY_DOWN:
        currentWindow->keyState.view.down = down;
        break;
    case GLUT_KEY_LEFT:
        currentWindow->keyState.view.left = down;
        break;
    case GLUT_KEY_RIGHT:
        currentWindow->keyState.view.right = down;
        break;
    }

}
void MainWindow::handleInput()
{
    vec3 dir((currentWindow->keyState.forward - currentWindow->keyState.backward) * cos(currentWindow->localPlayer->viewAngle.y)
            -(currentWindow->keyState.right - currentWindow->keyState.left) * sin(currentWindow->localPlayer->viewAngle.y)
            , (currentWindow->keyState.forward - currentWindow->keyState.backward) * sin(currentWindow->localPlayer->viewAngle.y)
            +(currentWindow->keyState.right - currentWindow->keyState.left) * cos(currentWindow->localPlayer->viewAngle.y)
            , 0.0f);
    
    //std::cout << currentWindow->localPlayer->viewAngle.y << ' , ' << cos(currentWindow->localPlayer->viewAngle.y) << ' ,' << sin(currentWindow->localPlayer->viewAngle.y) << std::endl;
    std::cout << (currentWindow->keyState.right - currentWindow->keyState.left) << std::endl;
    dir = dir.normalize();
    currentWindow->camPosition.x += dir.x*0.1f;
    currentWindow->camPosition.y += dir.y*0.1f;
    //std::cout << currentWindow->camPosition.x << " , " << currentWindow->camPosition.y << std::endl;
    
    currentWindow->localPlayer->viewAngle.y +=  (currentWindow->keyState.view.right - currentWindow->keyState.view.left)*0.1f;
    currentWindow->localPlayer->viewAngle.x +=  (currentWindow->keyState.view.up - currentWindow->keyState.view.down)*0.1f;
}
void MainWindow::mouseCallback(int x, int y)
{
    float centerx = glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2.f;
	float centery = glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2.f;
	float d_angle = 0.1f;
	float sensitivity = 0.25f;

	//Confine mouse
	glutWarpPointer(centerx, centery);

	currentWindow->localPlayer->viewAngle.y += (x - centerx) * d_angle * sensitivity;
	currentWindow->localPlayer->viewAngle.x += (y - centery) * d_angle * sensitivity;

	currentWindow->localPlayer->viewAngle = currentWindow->localPlayer->viewAngle.clamp();
	//currentWindow->localPlayer->rotation = mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.x, 1.0f, 0.0f, 0.0f) * mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.y, 0.0f, 1.0f, 0.0f);

}
void MainWindow::timerCallback(int)
{
    //demande de rappel de cette fonction dans 25ms
    glutTimerFunc(25, timerCallback, 0);

    currentWindow->localPlayer->updateView();
    currentWindow->handleInput();

    //reactualisation de l'affichage
    glutPostRedisplay();
}

void MainWindow::loadData()
{
    // Chargement du shader
    shaderProgramId = read_shader("data/shader.vert", "data/shader.frag");

    //matrice de projection
    projection = mat4::matrice_projection(80.0f*M_PI/180.0f,16.0f/9.0f,0.01f,100.0f);
    glUniformMatrix4fv(get_uni_loc(shaderProgramId,"projection"),1,false,projection.pointeur()); PRINT_OPENGL_ERROR();

    localPlayer = new Player();

    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST); PRINT_OPENGL_ERROR();

    props.push_back(Table());
    props.push_back(Floor());

	//hide cursor
}

void MainWindow::Run()
{
    glutMainLoop();
}

