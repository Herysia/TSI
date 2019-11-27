#version 120

//Un Fragment Shader minimaliste
void main (void)
{

    float x = 2 * gl_FragCoord.x/600.0 - 1;
    float y = 2 * gl_FragCoord.y/600.0 - 1;
    float r=0.0;
    float g=1.0;
    if(sqrt(x*x+y*y)<0.3) {
        r=1.0;
        g=0.0;
    }

    //couleur du fragment
    gl_FragColor = vec4(r,g,0.0,1.0);
}
