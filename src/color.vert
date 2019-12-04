#version 120

uniform mat4 rotation_model;
uniform vec4 rotation_center_model;
uniform vec4 translation_model;
uniform vec3 color_model;

uniform mat4 rotation_view;
uniform vec4 rotation_center_view;
uniform vec4 translation_view;

uniform mat4 projection;

varying vec3 color;

//Un Vertex Shader minimaliste
void main (void)
{
    //application de la deformation du model
    vec4 p_model = rotation_model*(gl_Vertex-rotation_center_model)+rotation_center_model+translation_model;
    //application de la deformation de la vue
    vec4 p_modelview = rotation_view*(p_model-rotation_center_view)+rotation_center_view+translation_view;
    //Projection du sommet
    vec4 p_proj = projection*p_modelview;
    
    //copie du param color
    color = color_model.xyz;

    //position dans l'espace ecran
    gl_Position = p_proj;
}
