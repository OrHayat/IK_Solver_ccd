#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform int id;
void main()
{

int r = (id & 0x000000FF) >>  0;
int g = (id & 0x0000FF00) >>  8;
int b = (id & 0x00FF0000) >> 16;
vec3 color=vec3(r/255.0f,g/255.0f,b/255.0f);
gl_FragColor =vec4(color,1);
}
