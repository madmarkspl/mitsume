#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

enum Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

struct Movement
{
	Movement() : F(false), B(false), L(false), R(false) {}
	GLboolean F, B, L, R;
};

class CCamera
{
public:
	CCamera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	CCamera();
	~CCamera();

	glm::mat4 getViewMatrix() const;
	float getZoom() const;

	void setDirection(Direction dir, GLuint action);
	void move();
	void lookAround(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	void zoom(GLfloat offset);

private:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	GLfloat _yaw;
	GLfloat _pitch;

	glm::vec3 _moveFB;
	glm::vec3 _moveLR;
	Movement _movement;
	GLfloat _movementSpeed;
	GLfloat _mouseSens;
	GLfloat _zoom;

	void updateCameraVectors();

};
