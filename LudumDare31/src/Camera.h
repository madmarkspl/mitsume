#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class CCamera
{
public:
	CCamera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	CCamera();
	~CCamera();

	glm::mat4 getViewMatrix();

private:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	GLfloat _yaw;
	GLfloat _pitch;

	GLfloat _movementSpeed;
	GLfloat _mouseSens;
	GLfloat _zoom;

	void updateCameraVectors();

};
