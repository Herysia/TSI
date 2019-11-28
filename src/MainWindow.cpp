#include "MainWindow.hpp"

MainWindow::MainWindow()
{
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
    glutInitWindowSize(600, 600);

    //Titre de la fenetre
    glutCreateWindow("OpenGL");

    //Fonction de la boucle d'affichage
    ::glutDisplayFunc(MainWindow::displayCallback);

    //Fonction de gestion du clavier
    ::glutKeyboardFunc(MainWindow::keyboardCallback);

    //Fonction d'appel d'affichage en chaine
    ::glutTimerFunc(25, MainWindow::timerCallback, 0);
	//Fonction de gestion de souris
	//glutPassiveMotionFunc(mouseCallback);
    //Fonction des touches speciales du clavier (fleches directionnelles)
    glutSpecialFunc(specialCallback);
    //Initialisation des fonctions OpenGL
    glewInit();

    //Notre fonction d'initialisation des donnees et chargement des shaders
    loadData();
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
        it->Draw();
    }
    std::cout << currentWindow->localPlayer->rotation.pointeur() << std::endl;
    //Changement de buffer d'affichage pour eviter un effet de scintillement
    glutSwapBuffers();
}
void MainWindow::keyboardCallback(unsigned char key, int, int)
{    
    switch (key)
    {
    case 27://escape
        exit(0);
        break;
    }
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
	std::cout << currentWindow->localPlayer->viewAngle.y*180.0f/M_PI << " ; " << currentWindow->localPlayer->viewAngle.x*180.0f/M_PI << std::endl;
	currentWindow->localPlayer->rotation = mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.x, 1.0f, 0.0f, 0.0f) * mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.y, 0.0f, 1.0f, 0.0f);
}
void MainWindow::specialCallback(int key, int,int)
{
    float dL=0.03f;
    switch (key)
    {
    case GLUT_KEY_UP:
        currentWindow->localPlayer->viewAngle.x += dL; //rotation avec la touche du haut
        break;
    case GLUT_KEY_DOWN:
        currentWindow->localPlayer->viewAngle.x -= dL; //rotation avec la touche du bas
        break;
    case GLUT_KEY_LEFT:
        currentWindow->localPlayer->viewAngle.y -= dL; //rotation avec la touche de gauche
        break;
    case GLUT_KEY_RIGHT:
        currentWindow->localPlayer->viewAngle.y += dL; //rotation avec la touche de droite
        break;
    }
	currentWindow->localPlayer->viewAngle = currentWindow->localPlayer->viewAngle.clamp();
	std::cout << currentWindow->localPlayer->viewAngle.y*180.0f/M_PI << " ; " << currentWindow->localPlayer->viewAngle.x*180.0f/M_PI << std::endl;
	currentWindow->localPlayer->rotation = mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.x, 1.0f, 0.0f, 0.0f) * mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.y, 0.0f, 1.0f, 0.0f);
    glutPostRedisplay();
}
void MainWindow::timerCallback(int)
{
    //demande de rappel de cette fonction dans 25ms
    glutTimerFunc(25, timerCallback, 0);

    //reactualisation de l'affichage
    glutPostRedisplay();
}

void MainWindow::loadData()
{
    // Chargement du shader
    shaderProgramId = read_shader("data/shader.vert", "data/shader.frag");

    //matrice de projection
    projection = mat4::matrice_projection(60.0f*M_PI/180.0f,1.0f,0.01f,100.0f);
    glUniformMatrix4fv(get_uni_loc(shaderProgramId,"projection"),1,false,projection.pointeur()); PRINT_OPENGL_ERROR();

    localPlayer = new Entity();
    //centre de rotation de la 'camera' (les objets sont centres en z=-2)
    localPlayer->rotationCenter = vec3(0.0f,0.0f,-2.0f);

    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST); PRINT_OPENGL_ERROR();

    props.push_back(Table());
    props.push_back(Floor());

	//hide cursor
	glutSetCursor(GLUT_CURSOR_NONE);
}

void MainWindow::Run()
{
    glutMainLoop();
}

