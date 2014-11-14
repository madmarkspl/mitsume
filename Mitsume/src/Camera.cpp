#include "Camera.h"

CCamera::CCamera()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);
	_yaw = -90.0f;
	_pitch = 0.0f;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_movementSpeed = 5.0f;
	_mouseSens = 0.25f;
	_zoom = 45.0f;

	updateCameraVectors();
}

CCamera::CCamera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	_position = position;
	_up = up;
	_yaw = yaw;
	_pitch = pitch;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_movementSpeed = 5.0f;
	_mouseSens = 0.25f;
	_zoom = 45.0f;

	updateCameraVectors();
}

CCamera::~CCamera()
{
}

glm::mat4 CCamera::getViewMatrix()
{
	return glm::lookAt(_position, _position + _front, _worldUp);
}

void CCamera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(front);
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_front, _right));
}