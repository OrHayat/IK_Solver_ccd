#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform int id;


void main()
{
    vec3 c = color0 ;
    if(texCoord0.x>0.95||texCoord0.y>0.95||texCoord0.y<=0.05||texCoord0.x<=0.05)
    c=vec3(0,0,0);
    else{
	c=clamp(c, 0.0, 1.0);
	if(normal0.x>0){
	c=vec3(0,0,1);}
	if(normal0.x<0){
	c=vec3(0,1,0);}
	if(normal0.y<0){
	c=vec3(0,1,1);}
	if(normal0.y>0){
		c=vec3(1,0,0);
	}
	if(normal0.z<0){
		c=vec3(1,0,1);
	}
	if(normal0.z>0){
		c=vec3(1,1,0);
			}
}

	gl_FragColor = vec4(c.xyz,1);
}
