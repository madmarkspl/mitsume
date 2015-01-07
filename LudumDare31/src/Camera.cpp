#include <iostream>
#include "Camera.h"

CCamera::CCamera()
{
	_position = glm::vec3(-2.0f, 0.0f, 4.0f);
	_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_yaw = -90.0f;
	_pitch = 0.0f;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_movementSpeed = 0.1f;
	_mouseSens = 0.1f;
	_zoom = 45.0f;
	//_move = glm::vec3(0.0f, 0.0f, 0.0f);

	updateCameraVectors();
}

CCamera::CCamera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	_position = position;
	_worldUp = up;
	_yaw = yaw;
	_pitch = pitch;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_movementSpeed = 0.1f;
	_mouseSens = 0.25f;
	_zoom = 45.0f;
	//_move = glm::vec3(1.0f, 0.0f, 0.0f);

	updateCameraVectors();
}

CCamera::~CCamera()
{
}

glm::mat4 CCamera::getViewMatrix() const
{
	return glm::lookAt(_position, _position + _front, _worldUp);
}

float CCamera::getZoom() const
{
	return _zoom;
}

void CCamera::setDirection(Direction dir, GLuint action)
{
	if (dir == FORWARD && action == 1)
		_movement.F = true;
	else if (dir == FORWARD && action == 0)
		_movement.F = false;

	if (dir == BACKWARD && action == 1)
		_movement.B = true;
	else if (dir == BACKWARD && action == 0)
		_movement.B = false;

	if (dir == LEFT && action == 1)
		_movement.L = true;
	else if (dir == LEFT && action == 0)
		_movement.L = false;

	if (dir == RIGHT && action == 1)
		_movement.R = true;
	else if (dir == RIGHT && action == 0)
		_movement.R = false;
}

void CCamera::move()
{
	glm::vec3 mv;

	if (_movement.F)
		mv += _front;
	if (_movement.B)
		mv -= _front;
	if (_movement.L)
		mv -= _right;
	if (_movement.R)
		mv += _right;

	if (glm::length(mv) != 0)
		mv = glm::normalize(mv);

	_position += mv * _movementSpeed;
	
	//std::cout << _position.x << " " << _position.y << " " << _position.z << std::endl;
}

void CCamera::lookAround(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= _mouseSens;
	yOffset *= _mouseSens;
	
	_yaw += xOffset;
	_pitch += yOffset;
	
	if (constrainPitch)
	{
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;
	}
	//std::cout << xOffset << " " << yOffset << " " << _yaw << " " << _pitch << std::endl;
	updateCameraVectors();
}

void CCamera::zoom(GLfloat offset)
{
	if (_zoom >= 1.0f && _zoom <= 45.0f)
		_zoom -= offset;
	if (_zoom <= 1.0f)
		_zoom = 1.0f;
	if (_zoom >= 45.0f)
		_zoom = 45.0f;
}

void CCamera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = static_cast<GLfloat>(glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch)));
	front.y = (GLfloat)glm::sin(glm::radians(_pitch));
	front.z = (GLfloat)glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	_front = glm::normalize(front);
	
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_front, _right));
}