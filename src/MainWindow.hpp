#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <sstream>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glut.h>

#include "glutils.hpp"
#include "mat4.hpp"
#include "Entity.hpp"
#include "Table.hpp"
#include "Floor.hpp"
#include "Player.hpp"
#include "RectangularBlock.hpp"
#include "MovingBlock.hpp"
#include "Portal.hpp"
#include "Key.hpp"

#include "levelDesign/Room1.hpp"
#include "levelDesign/Room2.hpp"
#include "levelDesign/Room3.hpp"
#include "levelDesign/Spawn.hpp"
#include "levelDesign/Corridor.hpp"

class MainWindow
{
public:
    MainWindow();
    void Run();
    void Init(int argc, char **argv);

private:
    static MainWindow *currentWindow;
    GLuint vbo;

    mat4 projection;
    Player *localPlayer;
    std::vector<Entity *> props;
    std::vector<Portal *> portals;

    keyboardKeyState keyState;


    static void displayCallback();
    static void timerCallback(int);
    void loadData();
    void handleInput();
    void DrawHUD();
    void DrawScene();

    inline static void resizeHandler(int width, int height) {
        //prevent resize for now
        //TODO: handle resize
        glutReshapeWindow(1366, 768);
    }
    //Inputs
    inline static void keyboardCallbackUp(unsigned char key, int x, int y)
    {
        currentWindow->keyboardCallback(key, x, y, false);
    }
    inline static void keyboardCallbackDown(unsigned char key, int x, int y)
    {
        currentWindow->keyboardCallback(key, x, y, true);
    }
    inline static void specialCallbackUp(int key, int x, int y)
    {
        currentWindow->specialCallback(key, x, y, false);
    }
    inline static void specialCallbackDown(int key, int x, int y)
    {
        currentWindow->specialCallback(key, x, y, true);
    }
    inline static void stopDrawingRules(int)
    {
        currentWindow->shouldDrawRules = false;
        currentWindow->corridor1->changePortalsState(true);
    }
    void keyboardCallback(unsigned char key, int, int, bool down); //down=1 -> key pressed down   /  down=0 -> key released
    void specialCallback(int key, int, int, bool down);
    static void mouseCallback(int x, int y);
    void drawString(float x, float y, const std::string &str);

    //GUI
    bool shouldDrawRules = true;

    Corridor* corridor0;
    Corridor* corridor1;
    Corridor* corridor2;
    Corridor* corridor3;
protected:
};

#endif //MAIN_WINDOW_H