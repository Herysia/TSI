#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdlib.h>
#include "glutils.hpp"
#include "image.hpp"

extern GLuint shaderProgramIdColored;

#define Abs(x) (x >= 0 ? x : -x)
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
struct keyboardKeyState
{
    bool forward = false;
    bool backward = false;
    bool right = false;
    bool left = false;
    bool jump = false;
    struct View
    {
        bool up = false;
        bool down = false;
        bool right = false;
        bool left = false;
    };
    View view;
};
class vec4
{
public:
    vec4(float x, float y, float z, float w){
        this->x = x;this->y = y;this->z = z;this->w = w;
    }
    float x,y,z,w;
};
#endif //GLOBAL_H