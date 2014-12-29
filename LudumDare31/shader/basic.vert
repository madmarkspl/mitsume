#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vertPosition;
out vec3 vertNormal;
out vec4 vertColor;
out vec2 vertTexture;

void main()
{
	vertPosition = position;
	vertNormal = normal;
	vertColor = color;
	vertTexture = texture;

	vec4 pos = proj * view * model * vec4(position, 1.0);
	gl_Position = pos;
}