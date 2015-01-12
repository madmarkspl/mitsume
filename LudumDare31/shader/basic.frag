#version 400 core

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform sampler2D diffuse;

uniform PointLight light;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3 vertPosition;
in vec3 vertNormal;
in vec4 vertColor;
in vec2 vertTexture;

out vec4 outColor;

float rand(vec2 co){ return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453); }

void main()
{
	//mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 normal = normalize(vertNormal);

	vec3 fragPosition = vec3(vec4(vertPosition, 1.0));

	vec3 lightDir = normalize(light.position - fragPosition);

	float diff = max(dot(normal, lightDir), 0.0);

	float distance = length(light.position - fragPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	vec3 ambient = light.ambient * vec3(texture(diffuse, vertTexture));
	vec3 diffuse = light.diffuse * vec3(texture(diffuse, vertTexture));
	ambient *= attenuation;
	diffuse *= attenuation;
	
	float z = vertPosition.z;

	diffuse = mix(diffuse, vec3(0.0, 0.0, 0.0), z);
	
	outColor = vec4(ambient + diffuse, 1.0);
}