#version 120

varying vec3 color;

//Un Fragment Shader minimaliste
void main (void)
{
    gl_FragColor = vec4(color.x,color.y,color.z,1.0);
}
