#ifndef ENTITY_H
#define ENTITY_H
#include "mesh.hpp"
#include "vec3.hpp"
#include "mat4.hpp"
#include "glutils.hpp"
#include "global.hpp"

class Entity
{
public:
    Entity();
    mat4 rotation;
    vec3 rotationCenter;
    vec3 translation;

    void Draw(const vec3& camPosition);
    GLuint textureId;
private:
protected:
    mesh m;
    int nbTriangles;
    GLuint vbo;
    GLuint vboi;
};

#endif //ENTITY_H