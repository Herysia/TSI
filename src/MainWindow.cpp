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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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

    currentWindow->DrawScene();
    currentWindow->DrawHUD();
    //Changement de buffer d'affichage pour eviter un effet de scintillement
    glutSwapBuffers();
}
void MainWindow::drawString(float x, float y, const std::string &str)
{
	glUseProgram(0);
    glColor3f(1., 0., 0.);
    
    glRasterPos2d(x, y);
    for (unsigned int n=0; n<str.size(); ++n) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[n]);
    }
}
void MainWindow::DrawHUD()
{
    if(shouldDrawRules)
    {
        drawString(-0.22f, 0.0f, "Ramassez tous les cubes rouges");
        //once
        static bool swap = true;
        if(swap)
        {
            glutTimerFunc(5000, stopDrawingRules, 0);
            swap = true;
        }
    }
    //Drawing score
    std::ostringstream oss;
    oss << currentWindow->localPlayer->getScore() << " / " << Key::maxScore;
    std::string scoreString = oss.str();
    drawString(0.9f, -0.95f, scoreString);

    //Drawing victory
    if(currentWindow->localPlayer->getScore() ==Key::maxScore)
    {
        drawString(-0.05f, 0.0f, "BRAVO !!");
    }

}
//Code adapted from https://github.com/ThomasRinsma/opengl-game-test/blob/86d4dcfccdfe067d6154ff94992e347856578632/src/scene.cc
void MainWindow::DrawScene()
{
    for(auto portal : currentWindow->portals)
    {
        if(!portal->state)
            continue;
        //Draw portal on stencil buffer
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
        glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);
        glStencilMask(0xFF);
        portal->Draw(currentWindow->localPlayer->getCamPosition());
        //Draw inner portal
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);
        
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0x00);
        glStencilFunc(GL_EQUAL, 1, 0xFF);

        //EnableClipping & correct angle
        vec3 normal(0.0f, 0.0f, 1.0f);
        float sgn = 1.0f;
        if(portal->other->axis == Portal::ZAXIS)
            normal = vec3(1.0f, 0.0f, 0.0f);
        if(portal->other->dir == Portal::NEGATIVE)
            sgn = -1.0f;
        normal = normal*sgn;

        float deltaY = portal->getViewDelta();
        currentWindow->localPlayer->setPortalView(deltaY);
        vec3 detlaPos = portal->getPosDelta(currentWindow->localPlayer->getCamPosition(), deltaY);
        glUseProgram(shaderProgramIdColored);
        glUniform4f(get_uni_loc(shaderProgramIdColored, "clip_plane"), normal.x, normal.y, normal.z, -sgn*(portal->other->axis==Portal::ZAXIS ? portal->other->getAABB().max.x : portal->other->getAABB().max.z));
        glUniformMatrix4fv(get_uni_loc(shaderProgramIdColored, "rotation_view"), 1, false, currentWindow->localPlayer->rotation.pointeur());

        for(auto &prop : currentWindow->props)
        {
            prop->Draw(currentWindow->localPlayer->getCamPosition()+detlaPos);
        }

        //Disable Clipping & correct angle
        currentWindow->localPlayer->resetPortalView();
        glUseProgram(shaderProgramIdColored);
        glUniform4f(get_uni_loc(shaderProgramIdColored, "clip_plane"), 0.0f, 0.0f, 0.0f, 0.0f);
        glUniformMatrix4fv(get_uni_loc(shaderProgramIdColored, "rotation_view"), 1, false, currentWindow->localPlayer->rotation.pointeur());

        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0xFF);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

        glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);

        portal->Draw(currentWindow->localPlayer->getCamPosition());
    }

	glDisable(GL_STENCIL_TEST);
	glStencilMask(0x00);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_ALWAYS);
	glClear(GL_DEPTH_BUFFER_BIT);
	for(auto portal : currentWindow->portals)
    {
        if(!portal->state)
            continue;
		portal->Draw(currentWindow->localPlayer->getCamPosition());
    }
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0x00);
	glStencilFunc(GL_EQUAL, 0, 0xFF);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);


    for (auto &ent : currentWindow->props)
    {
        ent->Draw(currentWindow->localPlayer->getCamPosition());
    }
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

    currentWindow->handleInput();
    currentWindow->localPlayer->applyPhysics();
    currentWindow->localPlayer->resetSkippedCollision();
    for (auto &portal : currentWindow->portals)
    {
        if(!portal->state)
            continue;
        if(currentWindow->localPlayer->checkPortalCollision(*portal))
            break;//If teleport has occured
    }
    //for (std::vector<Entity *>::iterator it = currentWindow->props.begin(); it != currentWindow->props.end(); ++it)
    for (auto &ent : currentWindow->props)
    {
        ent->updatePosition();
        if(currentWindow->localPlayer->noClipMode)
            continue;
        currentWindow->localPlayer->correctPosition(*ent);
    }
    //reactualisation de l'affichage (toutes les 25ms)
    if (i >= 5)
    {
        currentWindow->localPlayer->updateView();
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
    projection = mat4::matrice_projection(80.0f * M_PI / 180.0f, 16.0f / 9.0f, 0.01f, 100.0f);

    glUseProgram(shaderProgramIdColored);
    //matrice de projection
    glUniformMatrix4fv(get_uni_loc(shaderProgramIdColored, "projection"), 1, false, projection.pointeur());
    glUniform4f(get_uni_loc(shaderProgramIdColored, "clip_plane"), 0.0f, 0.0f, 0.0f, 0.0f);
    PRINT_OPENGL_ERROR();

    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_DISTANCE0);
    PRINT_OPENGL_ERROR();

    glUseProgram(shaderProgramIdTextured);
    glUniformMatrix4fv(get_uni_loc(shaderProgramIdTextured, "projection"), 1, false, projection.pointeur());
    PRINT_OPENGL_ERROR();

    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_DISTANCE0);
    PRINT_OPENGL_ERROR();

    localPlayer = new Player();
    //Initialising number of keys to 0
    Key::maxScore = 0;
    Spawn spawn(props, portals);

    //Main room corridors
    corridor0 = new Corridor(props, portals);
    corridor1 = new Corridor(props, portals, vec3(5.0f,0.0f,5.0f));
    corridor2 = new Corridor(props, portals, vec3(5.0f,0.0f,0.0f));
    corridor3 = new Corridor(props, portals, vec3(0.0f,0.0f,5.0f));
    
    //Corridor 0 room1 fun
    Portal* p1 = new Portal(vec2(0.0f,11.0f), vec2(1.5f,13.0f), 2.97f, Portal::XAXIS, Portal::NEGATIVE);
    Portal* p2 = new Portal(vec2(-2.0f,0.0f), vec2(-0.5f,2.0f), -9.97f, Portal::ZAXIS, Portal::POSITIVE);
    corridor0->setupPx(p1, p2);
    p1 = new Portal(vec2(0.0f,11.0f), vec2(1.5f,13.0f), 2.97f, Portal::ZAXIS, Portal::NEGATIVE);
    p2 = new Portal(vec2(0.5f,0.0f), vec2(2.0f,2.0f), -9.97f, Portal::ZAXIS, Portal::POSITIVE);
    corridor0->setupPz(p1, p2);

    //Corridor 1 spawn to room 1
    p1 = new Portal(vec2(5.0f,11.0f), vec2(6.5f,13.0f), 7.97, Portal::XAXIS, Portal::NEGATIVE);
    p2 = new Portal(vec2(-9.25f,11.0f), vec2(-7.75f,13.0f), -7.03f, Portal::XAXIS, Portal::NEGATIVE);
    corridor1->setupPx(p1, p2);
    p1 = new Portal(vec2(5.0f,11.0f), vec2(6.5f,13.0f), 7.97f, Portal::ZAXIS, Portal::NEGATIVE);
    p2 = new Portal(vec2(0.5f,0.0f), vec2(2.0f,2.0f), 9.97f, Portal::ZAXIS, Portal::NEGATIVE);
    corridor1->setupPz(p1, p2);
    corridor1->changePortalsState(false);

    //Corridor 2 room 1 to room 2
    p1 = new Portal(vec2(5.0f,11.0f), vec2(6.5f,13.0f), 2.97, Portal::XAXIS, Portal::NEGATIVE);
    p2 = new Portal(vec2(-9.25f,11.0f), vec2(-7.75f,13.0f), -7.03f, Portal::XAXIS, Portal::NEGATIVE);
    corridor1->setupPx(p1, p2);
    p1 = new Portal(vec2(0.0f,11.0f), vec2(1.5f,13.0f), 7.97f, Portal::ZAXIS, Portal::NEGATIVE);
    p2 = new Portal(vec2(-9.25f,11.0f), vec2(-7.75f,13.0f), -7.03f, Portal::XAXIS, Portal::NEGATIVE);
    corridor1->setupPz(p1, p2);
    corridor1->changePortalsState(false);
    
    Room1 room1(props, corridor1, corridor2);
    Room2 room2(props, portals, corridor2, corridor3);
    
}

void MainWindow::Run()
{
    glutMainLoop();
}
