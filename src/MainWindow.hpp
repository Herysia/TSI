#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <list>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glut.h>

#include "glutils.hpp"
#include "mat4.hpp"
#include "Entity.hpp"
#include "Table.hpp"
#include "Floor.hpp"
#include "Triangle.hpp"

class MainWindow
{    
public:
    
    MainWindow();
    void Run();
    void Init(int argc, char** argv);
private:

    static MainWindow* currentWindow;
    GLuint vbo;

    mat4 projection;
    Entity* localPlayer;
    std::list<Entity> props;
    Triangle* tr;

    static void displayCallback();
    static void timerCallback(int);
    void loadData();

    //Inputs
    static void keyboardCallback(unsigned char key, int, int);
    static void mouseCallback(int x, int y);
    static void specialCallback(int key, int,int);

protected:
};

#endif //MAIN_WINDOW_H