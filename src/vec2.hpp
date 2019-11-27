
#pragma once

#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>


/** Une structure de vecteur 2D */

class vec2
{
    public:
    /** Coordonnee x */
    float x;
    /** Coordonnee y */
    float y;

    /** Constructeur vecteur (0,0) */
    vec2();
    /** Constructeur vecteur (x,y) */
    vec2(float x_param,float y_param);
    

    /** Somme vectorielle */
    vec2& operator+=(const vec2& v);
    /** Difference vectorielle */
    vec2& operator-=(const vec2& v);
    /** Multiplication par un scalaire */
    vec2& operator*=(float s);
    /** Division par un scalaire */
    vec2& operator/=(float s);

    /** Norme d'un vecteur */
    float norm() const&;
    /** Produit scalaire */
    float dot(const vec2& v1);

    /** Renvoie un vecteur de meme direction de norme 1 */
    vec2 normalize() const&;

    /** Affichage d'un vecteur sur la ligne de commande */
    std::ostream& operator<<(std::ostream& sout);

    /** Somme vectorielle */
    vec2 operator+(const vec2& v1) const&;
    /** Difference vectorielle */
    vec2 operator-(const vec2& v1) const&;
    /** Multiplication par un scalaire */
    vec2 operator*(float s) const&;
    /** Multiplication par un scalaire */
    vec2 operator*(float s) const&;
    /** Division par un scalaire */
    vec2 operator/(float s) const&;
};







#endif
