#version 120

//Un Vertex Shader minimaliste
void main (void)
{
    //Coordonnees du sommet
    vec4 p=gl_Vertex;
    gl_Position = p;
}
