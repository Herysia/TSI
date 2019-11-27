
#pragma once

#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
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
    vec3(float x_param,float y_param,float z_param);

    /** Somme vectorielle */
    vec3& operator+=(const vec3& v);
    /** Difference vectorielle */
    vec3& operator-=(const vec3& v);
    /** Multiplication par un scalaire */
    vec3& operator*=(float s);
    /** Division par un scalaire */
    vec3& operator/=(float s);
    
    /** Norme d'un vecteur */
    float norm() const&;
    /** Produit scalaire */
    float dot(const vec3& v1);
    /** Produit vectoriel */
    vec3 cross(const vec3& v1);

    /** Renvoie un vecteur de meme direction de norme 1 */
    vec3 normalize() const&;

    /** Affichage d'un vecteur sur la ligne de commande */
    std::ostream& operator<<(std::ostream& sout);

    /** Somme vectorielle */
    vec3 operator+(const vec3& v1) const&;
    /** Difference vectorielle */
    vec3 operator-(const vec3& v1) const&;
    /** Multiplication par un scalaire */
    vec3 operator*(float s) const&;
    /** Division par un scalaire */
    vec3 operator/(float s) const&;

    /** Applique mat4 sur un vec3 */
    //vec3 operator*(const mat4& m);
};








#endif
