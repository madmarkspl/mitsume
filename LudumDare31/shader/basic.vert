#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 vertColor;

void main()
{
	vertColor = color;
	vec4 pos = proj * view * model * vec4(position, 1.0);
	gl_Position = pos;
}