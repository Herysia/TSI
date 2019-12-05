
#pragma once

#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include "vec2.hpp"
//#include "mat4.hpp"
//class mat4;
/** Une structure de vecteur 3D */

class vec3
{
public:
    /** Coordonnee x */
    float x;
    /** Coordonnee y */
    float y;
    /** Coordonnee z */
    float z;

    /** Constructeur vecteur (0,0,0) */
    vec3();
    /** Constructeur vecteur (x,y,z) */
    vec3(float x_param, float y_param, float z_param);

    /** Somme vectorielle */
    vec3 &operator+=(const vec3 &v);
    /** Difference vectorielle */
    vec3 &operator-=(const vec3 &v);
    /** Multiplication par un scalaire */
    vec3 &operator*=(float s);
    /** Division par un scalaire */
    vec3 &operator/=(float s);

    /** Norme d'un vecteur */
    float norm() const;
    /** Produit scalaire */
    float dot(const vec3 &v1) const;
    /** Produit vectoriel */
    vec3 cross(const vec3 &v1) const;

    /** Projection sur le plan horizontal*/
    inline vec2 get2D() const
    {
        return vec2(x, z);
    }

    /** Renvoie un vecteur de meme direction de norme 1 */
    vec3 normalize() const;

    vec3 clamp() const;

    /** Affichage d'un vecteur sur la ligne de commande */
    friend std::ostream &operator<<(std::ostream &sout, const vec3 &vec);
};
/** Somme vectorielle */
vec3 operator+(const vec3 &v0, const vec3 &v1);
/** Difference vectorielle */
vec3 operator-(const vec3 &v0, const vec3 &v1);
/** Multiplication par un scalaire */
vec3 operator*(const vec3 &v0, float s);
/** Division par un scalaire */
vec3 operator/(const vec3 &v0, float s);

#endif
