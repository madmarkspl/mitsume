#version 400 core

in vec4 vertColor;

out vec4 outColor;

float rand(vec2 co){
	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
	outColor = vertColor;
}