#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glut.h>
#include "glutils.hpp"

class MainWindow
{    
    public:
    
    MainWindow(int argc, char** argv);

    void run();

    private:

    GLuint shaderProgramId;
    GLuint vbo;

    static void displayCallback();
    static void keyboardCallback(unsigned char key, int, int);
    static void timerCallback(int);
    void loadData();


    protected:
};

#endif //MAIN_WINDOW_H