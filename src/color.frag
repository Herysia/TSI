#version 120

varying vec3 color;
varying vec3 coord_3d;

uniform vec3 min;
uniform vec3 max;
uniform vec3 color_model;

//Un Fragment Shader minimaliste
void main (void)
{
    int i=0;
    const float width = 0.05f;
    if(abs(coord_3d.x-max.x)<=width)
    {
        i++;
    }
    if(abs(coord_3d.y-max.y)<=width)
    {
        i++;
    }
    if(abs(coord_3d.z-max.z)<=width)
    {
        i++;
    }
    if(abs(coord_3d.x-min.x)<=width)
    {
        i++;
    }
    if(abs(coord_3d.y-min.y)<=width)
    {
        i++;
    }
    if(abs(coord_3d.z-min.z)<=width)
    {
        i++;
    }
    if(i>=2)
    {
        gl_FragColor = vec4(0.0f,0.0f,0.0f,1.0f);
    }
    else
    {
        gl_FragColor = vec4(color_model.x,color_model.y,color_model.z,1.0);
    }
    
}
