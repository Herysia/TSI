
#ifndef MAT4_HPP
#define MAT4_HPP

#include <iostream>
#include "vec3.hpp"

/** Une structure de matrice de taille 4x4 */

class mat4
{
public:
    /** Initialise la matrice a l'identitee */
    mat4();
    /** Initialisation par valeur */
    mat4(float x00, float x01, float x02, float x03,
         float x10, float x11, float x12, float x13,
         float x20, float x21, float x22, float x23,
         float x30, float x31, float x32, float x33);

    /** Obtention des valeurs de la matrice sous la forme m(x,y) */
    float operator()(int x, int y) const;

    /** Modification des valeurs de la matrice sous la forme m(x,y)=... */
    float &operator()(int x, int y);

    /** Donnees de la matrice sous forme d'un tableau */
    float M[4 * 4];

    /** Produit de matrice */
    mat4 operator*(const mat4 &m2);
    
    inline void operator*=(float b) {
        for (int i = 0; i < 16; ++i) { M[i] *= b; }
    }
    inline void operator/=(float b) {
        operator*=(1.0f / b);
    }
    /** Recupere un pointeur sur les donnees de la matrice */
    const float *pointeur();

    /** Calcule la transposee d'une matrice */
    mat4 transpose();

    mat4 inverse() const;

    /** Construit une matrice de rotation ayant pour axe: (axe_x,axe_y,axe_z) et l'angle donne */
    static mat4 matrice_rotation(float angle, float axe_x, float axe_y, float axe_z);

    /** Construit une matrice de projection */
    //mat4 matrice_projection(float L,float H,float d_min,float d_max);
    static mat4 matrice_projection(float fov, float aspect, float d_min, float d_max);

    /** Construit une matrice de rotation pour une camera de position eye, regardant dans la direction center
     * et ayant pour position haute up 
     * WARNING : Extraire la partie translation à l'aide de la fonction extract_translation */
    static mat4 matrice_lookat(const vec3 &eye, const vec3 &center, const vec3 &up);

    /** Extrait et renvoie la translation d'un matrice de transformation */
    vec3 extract_translation();

    /** Construit une matrice n'ayant que des zeros */
    static mat4 matrice_zeros();

    /** Affichage d'une matrice sur la ligne de commande */
    std::ostream &operator<<(std::ostream &sout);
};
/** Applique mat4 sur un vec3 */
vec3 operator*(const mat4 &m, const vec3 &p);

#endif
