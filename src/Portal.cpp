#include "Portal.hpp"

Portal::Portal(vec2 min, vec2 max, float depth,  bool axis)
{
    shaderProgramId = shaderProgramIdColored;
    color = vec3(1,0,0);
    mode = MODE_AABB;
    this->axis = axis;
    glUseProgram(shaderProgramId);
    float sommets[3*4];
    if(axis == XAXIS)
    {
        aabb = AABB(vec3(min.x, min.y, depth), vec3(max.x, max.y, depth));
        sommets[3]=aabb.max.x;sommets[4]=aabb.min.y;sommets[5]=depth;
        sommets[9]=aabb.min.x;sommets[10]=aabb.max.y;sommets[11]=depth;
        
    }
    else
    {
        aabb = AABB(vec3(depth, min.y, min.x), vec3(depth, max.y, max.x));
        sommets[3]=depth;sommets[4]=aabb.min.y;sommets[5]=aabb.max.z;
        sommets[9]=depth;sommets[10]=aabb.max.y;sommets[11]=aabb.min.z;
    }
    sommets[0]=aabb.min.x;sommets[1]=aabb.min.y;sommets[2]=aabb.min.z;
    sommets[6]=aabb.max.x;sommets[7]=aabb.max.y;sommets[8]=aabb.max.z;
    pos = aabb.getCenter();
    // float sommets[] = {
    //     0,0,0,
    //     0,0,3,
    //     0,3,3,
    //     0,3,0
    // };
    // //tableau entrelacant coordonnees-normales
    unsigned int index[] = {
        0, 1, 2,
        2, 3, 0
    };
    nbTriangles = 2;
    glGenBuffers(1, &vbo);
    PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), sommets, GL_STATIC_DRAW);
    PRINT_OPENGL_ERROR();

    glEnableClientState(GL_VERTEX_ARRAY);
    PRINT_OPENGL_ERROR();
    // Indique que le buffer courant (désigné par la variable vbo) est utilisé pour les positions de sommets
    glVertexPointer(3, GL_FLOAT, sizeof(sommets), 0);
    PRINT_OPENGL_ERROR();

    //attribution d'un autre buffer de donnees
    glGenBuffers(1, &vboi);
    PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);
    PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
    PRINT_OPENGL_ERROR();
}

void Portal::Draw(const vec3 &camPosition)
{
    glUseProgram(shaderProgramId);
    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shaderProgramId, "rotation_model"), 1, false, rotation.pointeur());
        PRINT_OPENGL_ERROR();

        glUniform4f(get_uni_loc(shaderProgramId, "rotation_center_model"), rotationCenter.x, rotationCenter.y, rotationCenter.z, 0.0f);
        PRINT_OPENGL_ERROR();
        glUniform4f(get_uni_loc(shaderProgramId, "translation_model"), translation.x - camPosition.x, translation.y - camPosition.y, translation.z - camPosition.z, 0.0f);
        PRINT_OPENGL_ERROR();
        glUniform3f(get_uni_loc(shaderProgramId, "color_model"), color.x, color.y, color.z);
        PRINT_OPENGL_ERROR();
        glUniform3f(get_uni_loc(shaderProgramId, "min"), aabb.min.x, aabb.min.y, aabb.min.z);
        PRINT_OPENGL_ERROR();
        glUniform3f(get_uni_loc(shaderProgramId, "max"), aabb.max.x, aabb.max.y, aabb.max.z);
        PRINT_OPENGL_ERROR();
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    PRINT_OPENGL_ERROR();
    PRINT_OPENGL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);

    glDrawElements(GL_TRIANGLES, 3 * nbTriangles, GL_UNSIGNED_INT, 0);
    PRINT_OPENGL_ERROR();
}



void Portal::linkPortals(Portal* other)
{
    this->other = other;
    other->other = this;
}
//https://aras-p.info/texts/obliqueortho.html
mat4 const Portal::clippedProjMat(mat4 const &rotation, mat4 const &projMat) const
{
    vec3 normal(0.0f, 0.0f, 1.0f);
    if(axis == ZAXIS)
        normal = vec3(1.0f, 0.0f, 0.0f);
    vec3 clipPos(
        rotation.M[0]*pos.x + rotation.M[1]*pos.y + rotation.M[2]*pos.z + rotation.M[3],
        rotation.M[4]*pos.x + rotation.M[5]*pos.y + rotation.M[6]*pos.z + rotation.M[7],
        rotation.M[8]*pos.x + rotation.M[9]*pos.y + rotation.M[10]*pos.z + rotation.M[11]
    );
    vec3 clipNormal(
        rotation.M[0]*normal.x + rotation.M[1]*normal.y + rotation.M[2]*normal.z,
        rotation.M[4]*normal.x + rotation.M[5]*normal.y + rotation.M[6]*normal.z,
        rotation.M[8]*normal.x + rotation.M[9]*normal.y + rotation.M[10]*normal.z
    );

    //Clip plane Ax + By + Cz + D =0
    //clipNormal = vec3(A, B, C)
    float d = clipPos.dot(clipNormal);
    mat4 inv = projMat.inverse();
    float v4x = sgn(clipNormal.x);
    float v4y = sgn(clipNormal.y);
    float v4z = 1.0f;
    float v4w = 1.0f;
    
    float qx = rotation.M[0]*v4x + rotation.M[1]*v4y + rotation.M[2]*v4z + rotation.M[3]*v4w;
    float qy = rotation.M[4]*v4x + rotation.M[5]*v4y + rotation.M[6]*v4z + rotation.M[7]*v4w;
    float qz = rotation.M[8]*v4x + rotation.M[9]*v4y + rotation.M[10]*v4z + rotation.M[11]*v4w;
    float qw = rotation.M[12]*v4x + rotation.M[13]*v4y + rotation.M[14]*v4z + rotation.M[15]*v4w;

    float dot = clipNormal.x*qx + clipNormal.y*qy + clipNormal.z*qz + d*qw;
    qx=clipNormal.x * (2.0f/dot);
    qy=clipNormal.y * (2.0f/dot);
    qz=clipNormal.z * (2.0f/dot);
    qw=d * (2.0f/dot);
	mat4 newProj = projMat;
    newProj.M[2] = qx -projMat.M[3];
    newProj.M[6] = qy -projMat.M[7];
    newProj.M[10] = qz -projMat.M[11];
    newProj.M[11] = qw -projMat.M[15];
	return newProj;
} 