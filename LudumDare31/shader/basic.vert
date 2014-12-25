#version 400 core

layout(location = 0) in vec2 position;
//layout(location = 1) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 color;

out vec4 vertColor;

void main()
{
	vertColor = color;
	vec4 pos = model * vec4(position, 0.0, 1.0);
	gl_Position = pos;

	
}