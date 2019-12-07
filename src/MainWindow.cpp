#include "MainWindow.hpp"

MainWindow::MainWindow()
{
}
MainWindow *MainWindow::currentWindow = NULL;
void MainWindow::Init(int argc, char **argv)
{
    currentWindow = this;
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
    glutReshapeFunc(resizeHandler);



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
    glClearColor(0.5f, 0.6f, 0.9f, 1.0f);
    PRINT_OPENGL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PRINT_OPENGL_ERROR();

    // Affecte les parametres uniformes de la vue (identique pour tous les modeles de la scene)
    glUseProgram(shaderProgramIdColored);
    {
        //envoie de la rotation
        glUniformMatrix4fv(get_uni_loc(shaderProgramIdColored, "rotation_view"), 1, false, currentWindow->localPlayer->rotation.pointeur());
        PRINT_OPENGL_ERROR();

        //envoie du centre de rotation
        vec3 cv = currentWindow->localPlayer->rotationCenter;
        glUniform4f(get_uni_loc(shaderProgramIdColored, "rotation_center_view"), cv.x, cv.y, cv.z, 0.0f);
        PRINT_OPENGL_ERROR();

        //envoie de la translation
        vec3 tv = currentWindow->localPlayer->translation;
        glUniform4f(get_uni_loc(shaderProgramIdColored, "translation_view"), tv.x, tv.y, tv.z, 0.0f);
        PRINT_OPENGL_ERROR();
    }
    // Affecte les parametres uniformes de la vue (identique pour tous les modeles de la scene)
    glUseProgram(shaderProgramIdTextured);
    {
        //envoie de la rotation
        glUniformMatrix4fv(get_uni_loc(shaderProgramIdTextured, "rotation_view"), 1, false, currentWindow->localPlayer->rotation.pointeur());
        PRINT_OPENGL_ERROR();

        //envoie du centre de rotation
        vec3 cv = currentWindow->localPlayer->rotationCenter;
        glUniform4f(get_uni_loc(shaderProgramIdTextured, "rotation_center_view"), cv.x, cv.y, cv.z, 0.0f);
        PRINT_OPENGL_ERROR();

        //envoie de la translation
        vec3 tv = currentWindow->localPlayer->translation;
        glUniform4f(get_uni_loc(shaderProgramIdTextured, "translation_view"), tv.x, tv.y, tv.z, 0.0f);
        PRINT_OPENGL_ERROR();
    }

    for (std::vector<Entity *>::iterator it = currentWindow->props.begin(); it != currentWindow->props.end(); ++it)
    {
        (*it)->Draw(currentWindow->localPlayer->getCamPosition());
    }
    //Changement de buffer d'affichage pour eviter un effet de scintillement
    glutSwapBuffers();
}
void MainWindow::keyboardCallback(unsigned char key, int, int, bool down)
{
    switch (key)
    {
    case 27: //escape
        exit(0);
        break;
    case 'z':
        currentWindow->keyState.forward = down;
        currentWindow->localPlayer->noClipMode = false;
        break;
    case 's':
        currentWindow->keyState.backward = down;
        currentWindow->localPlayer->noClipMode = false;
        break;
    case 'q':
        currentWindow->keyState.left = down;
        currentWindow->localPlayer->noClipMode = false;
        break;
    case 'd':
        currentWindow->keyState.right = down;
        currentWindow->localPlayer->noClipMode = false;
        break;
    case 'Z':
        currentWindow->keyState.forward = down;
        currentWindow->localPlayer->noClipMode = true;
        break;
    case 'S':
        currentWindow->keyState.backward = down;
        currentWindow->localPlayer->noClipMode = true;
        break;
    case 'Q':
        currentWindow->keyState.left = down;
        currentWindow->localPlayer->noClipMode = true;
        break;
    case 'D':
        currentWindow->keyState.right = down;
        currentWindow->localPlayer->noClipMode = true;
        break;
    case ' ':
        currentWindow->keyState.jump = down;
        currentWindow->localPlayer->noClipMode = false;
    }
}

void MainWindow::specialCallback(int key, int, int, bool down)
{
    float dL = 0.03f;
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
    vec2 dir((currentWindow->keyState.forward - currentWindow->keyState.backward) * sin(currentWindow->localPlayer->getViewAngle().y) + (currentWindow->keyState.right - currentWindow->keyState.left) * cos(currentWindow->localPlayer->getViewAngle().y)
    , (currentWindow->keyState.right - currentWindow->keyState.left) * sin(currentWindow->localPlayer->getViewAngle().y) - (currentWindow->keyState.forward - currentWindow->keyState.backward) * cos(currentWindow->localPlayer->getViewAngle().y));
    currentWindow->localPlayer->setHorizontalSpeed(dir.normalize() * 0.02f);
    if(currentWindow->localPlayer->noClipMode)
        currentWindow->localPlayer->setVerticalSpeed(-(currentWindow->keyState.forward - currentWindow->keyState.backward) * sin(currentWindow->localPlayer->getViewAngle().x));
    
    currentWindow->localPlayer->handleJump(currentWindow->keyState.jump);
    currentWindow->localPlayer->rotateAngle((currentWindow->keyState.view.up - currentWindow->keyState.view.down) * 0.02f,
                                            (currentWindow->keyState.view.right - currentWindow->keyState.view.left) * 0.02f,
                                            0.0f);
}
void MainWindow::mouseCallback(int x, int y)
{
    float centerx = glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2.f;
    float centery = glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2.f;
    float d_angle = 0.1f;
    float sensitivity = 0.05f;

    //Confine mouse
    glutWarpPointer(centerx, centery);

    currentWindow->localPlayer->rotateAngle((y - centery) * d_angle * sensitivity,
                                            (x - centerx) * d_angle * sensitivity,
                                            0.0f);

    currentWindow->localPlayer->clampViewAngle();
    //currentWindow->localPlayer->rotation = mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.x, 1.0f, 0.0f, 0.0f) * mat4::matrice_rotation(currentWindow->localPlayer->viewAngle.y, 0.0f, 1.0f, 0.0f);
}
void MainWindow::timerCallback(int)
{
    //demande de rappel de cette fonction dans 5ms //engine
    static short i = 0;
    glutTimerFunc(5, timerCallback, 0);

    currentWindow->localPlayer->updateView();
    currentWindow->handleInput();
    currentWindow->localPlayer->applyPhysics();
    for (std::vector<Entity *>::iterator it = currentWindow->props.begin(); it != currentWindow->props.end(); ++it)
    {
        (*it)->updatePosition();
        if(currentWindow->localPlayer->noClipMode)
            continue;
        currentWindow->localPlayer->correctPosition(**it.base());
        /*
        if(currentWindow->localPlayer->checkCollision(*it.base()))
        {
            currentWindow->localPlayer->correctPosition(*it.base());
            std::cout << "1" << std::endl;
        }*/
    }
    //reactualisation de l'affichage (toutes les 15ms <=> 66.6fps)
    if (i >= 3)
    {
        glutPostRedisplay();
        i = 0;
    }
    i++;
}

void MainWindow::loadData()
{
    // Chargement du shader
    //TODO: shader for planes // color rendering for floor
    shaderProgramIdColored = read_shader("data/color.vert", "data/color.frag");
    shaderProgramIdTextured = read_shader("data/shader.vert", "data/shader.frag");

    glUseProgram(shaderProgramIdColored);
    //matrice de projection
    projection = mat4::matrice_projection(80.0f * M_PI / 180.0f, 16.0f / 9.0f, 0.01f, 100.0f);
    glUniformMatrix4fv(get_uni_loc(shaderProgramIdColored, "projection"), 1, false, projection.pointeur());
    PRINT_OPENGL_ERROR();

    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST);
    PRINT_OPENGL_ERROR();

    glUseProgram(shaderProgramIdTextured);
    projection = mat4::matrice_projection(80.0f * M_PI / 180.0f, 16.0f / 9.0f, 0.01f, 100.0f);
    glUniformMatrix4fv(get_uni_loc(shaderProgramIdTextured, "projection"), 1, false, projection.pointeur());
    PRINT_OPENGL_ERROR();

    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST);
    PRINT_OPENGL_ERROR();

    localPlayer = new Player();
    //props.push_back(Table(0.01f, 0.01f, 0.01f));
    //props.push_back(Table(0.02f, 0.02f, 0.02f));
    //props.push_back(RectangularBlock(props.back().getAABB().min, props.back().getAABB().max));
    //props.push_back(new Floor());//vec3(0.42f, 1.0f, 0.42f)
    //props.push_back(new RectangularBlock(vec3(3, -1, 3), vec3(6, 0, 6)));
    //Box
    props.push_back(new RectangularBlock(vec3(-10.0f, 0.0f, -10.0f), vec3(10.0f, 6.5f, 10.0f), true));

    //big stairs
    props.push_back(new RectangularBlock(vec3(2.5, 0.0f, -8.5), vec3(5.5f, 0.7f, -5.5)));//overlapping
    props.push_back(new RectangularBlock(vec3(5.5f, 0.0f, -8.5), vec3(8.5, 0.7f, -5.5)));
    props.push_back(new RectangularBlock(vec3(5.5, 0.7f, -5.5), vec3(8.5, 1.4f, -1.83)));
    props.push_back(new RectangularBlock(vec3(5.5, 1.4f, -1.83), vec3(8.5, 2.2f, 1.83)));
    props.push_back(new RectangularBlock(vec3(5.5, 2.1f, 1.83), vec3(8.5, 3.0f, 5.5)));
    props.push_back(new RectangularBlock(vec3(5.5, 3.0f, 5.5), vec3(8.5, 3.8f, 8.5)));

    //small jumps
    props.push_back(new RectangularBlock(vec3(3.5, 3.4f, 5.5), vec3(4.5, 3.8f, 8.5)));
    props.push_back(new RectangularBlock(vec3(1.5, 3.4f, 5.5), vec3(2.5, 3.8f, 8.5)));
    props.push_back(new RectangularBlock(vec3(-0.5, 3.4f, 5.5), vec3(0.5, 3.8f, 8.5)));
    props.push_back(new RectangularBlock(vec3(-2.5, 3.4f, 5.5), vec3(-1.5, 3.8f, 8.5)));
    props.push_back(new RectangularBlock(vec3(-4.5, 3.4f, 5.5), vec3(-3.5, 3.8f, 8.5)));
    
    //tiny path
    props.push_back(new RectangularBlock(vec3(-8.5, 3.4f, 5.5), vec3(-5.5, 3.8f, 8.5)));
    props.push_back(new RectangularBlock(vec3(-7.2, 3.4f, -5.5), vec3(-6.8, 3.8f, 5.5)));
    props.push_back(new RectangularBlock(vec3(-8.5, 3.4f, -8.5), vec3(-5.5, 3.8f, -5.5)));
    
    //autostairs
    props.push_back(new RectangularBlock(vec3(-5.5, 3.4f, -8.5), vec3(-4.5, 3.8f, -5.5)));
    props.push_back(new RectangularBlock(vec3(-4.5, 3.8f, -8.5), vec3(-3.5, 3.9f, -5.5)));
    props.push_back(new RectangularBlock(vec3(-3.5, 3.9f, -8.5), vec3(-2.5, 4.0f, -5.5)));
    props.push_back(new RectangularBlock(vec3(-2.5, 4.0f, -8.5), vec3(-1.5, 4.1f, -5.5)));
    props.push_back(new RectangularBlock(vec3(-1.5, 4.1f, -8.5), vec3(-0.5, 4.2f, -5.5)));
    props.push_back(new RectangularBlock(vec3(-0.5, 4.2f, -8.5), vec3(0.5, 4.3f, -5.5)));
    props.push_back(new RectangularBlock(vec3(0.5, 4.3f, -8.5), vec3(1.5, 4.4f, -5.5)));
    props.push_back(new RectangularBlock(vec3(1.5, 4.4f, -8.5), vec3(2.5, 4.5f, -5.5)));
    props.push_back(new RectangularBlock(vec3(2.5, 4.5f, -8.5), vec3(3.5, 4.6f, -5.5)));
    props.push_back(new RectangularBlock(vec3(3.5, 4.6f, -8.5), vec3(4.5, 4.7f, -5.5)));
    props.push_back(new RectangularBlock(vec3(4.5, 4.7f, -8.5), vec3(5.5, 4.8f, -5.5)));
    props.push_back(new RectangularBlock(vec3(5.5, 4.8f, -8.5), vec3(10, 4.9f, -5.5)));
    //plane for the slope
    props.push_back(new Floor(vec3(-5.6, 3.8f, -8.5), vec3(5.5, 4.92f, -8.5), vec3(5.5, 4.92f, -5.5), vec3(-5.6, 3.8f, -5.5)));

    Elevator* elevator = new Elevator(vec3(1, 0.0f, 0), vec3(4, 0.1f, 3));
    elevator->setMinMax(0, 4.9);
    elevator->setSpeed(0.01f);
    props.push_back(elevator);

}

void MainWindow::Run()
{
    glutMainLoop();
}
