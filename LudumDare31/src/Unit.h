#pragma once
#include <glm/glm.hpp>
#include "Components.h"
#include "Batch.h"

class CUnit
{
	friend class CUnitGraphicsComponent;
	friend class CUnitInputComponent;
public:
	CUnit(glm::vec3 position, glm::vec3 rotation, float width, float height, float velocity, glm::vec4 color, GLuint textureID);

	~CUnit();

	void input();
	void update();
	void draw(CRenderer& renderer);

private:
	glm::vec3 _position;
	glm::vec3 _rotation;
	float _velocity;
	float _width;
	float _height;

	CInputComponent* _input;
	CPhysicsComponent* _physics;
	CHealthComponent* _health;
	CGraphicsComponent* _graphics;
	CAudioComponent* _audio;
};

class CUnitInputComponent : public CInputComponent
{
public:
	CUnitInputComponent() {};
	~CUnitInputComponent() {};

	void update(CUnit& unit);

private:
	glm::vec3 _moveVector;
};

class CUnitPhysicsComponent : public CPhysicsComponent
{
public:
	CUnitPhysicsComponent() {};
	~CUnitPhysicsComponent() {};

	void update(CUnit& unit);

private:

};

class CUnitHealthComponent : public CHealthComponent
{
public:
	CUnitHealthComponent() {};
	~CUnitHealthComponent() {};

	void update(CUnit& unit);

private:
};

class CUnitGraphicsComponent : public CGraphicsComponent
{
public:
	CUnitGraphicsComponent(glm::vec3 pos, glm::vec3 rot, float width, float height, glm::vec4 color, GLuint textureID) :
		_color(color), _textureID(textureID),_vertices(36)
	{
		float x = (float)((rand() % 100) / 100.0);
		float y = (float)((rand() % 100) / 100.0);
		float z = (float)((rand() % 100) / 100.0);
		_config = BatchConfig(GL_TRIANGLES, 0, textureID);
		//_config._transformMatrix = glm::translate(_config._transformMatrix, pos);
		//_config._transformMatrix = glm::rotate(_config._transformMatrix, 30.0f, glm::vec3(x, y, z));
		

		float halfWidth = width / 2;
		float halfHeight = height / 2;
		float halfDepth = width / 2;

		_vertices[0]._position.x = halfWidth;
		_vertices[0]._position.y = halfHeight;
		_vertices[0]._position.z = halfDepth;

		_vertices[1]._position.x = halfWidth;
		_vertices[1]._position.y = -halfHeight;
		_vertices[1]._position.z = halfDepth;

		_vertices[2]._position.x = -halfWidth;
		_vertices[2]._position.y = -halfHeight;
		_vertices[2]._position.z = halfDepth;

		_vertices[3]._position.x = -halfWidth;
		_vertices[3]._position.y = -halfHeight;
		_vertices[3]._position.z = halfDepth;

		_vertices[4]._position.x = -halfWidth;
		_vertices[4]._position.y = halfHeight;
		_vertices[4]._position.z = halfDepth;

		_vertices[5]._position.x = halfWidth;
		_vertices[5]._position.y = halfHeight;
		_vertices[5]._position.z = halfDepth;

		for (unsigned int i = 0; i < 6; ++i)
		{
			_vertices[i]._normal = glm::vec3(0.0f, 0.0f, 1.0f);
			_vertices[i]._color = _color;
		}

		_vertices[6]._position.x = -halfWidth;
		_vertices[6]._position.y = halfHeight;
		_vertices[6]._position.z = -halfDepth;

		_vertices[7]._position.x = -halfWidth;
		_vertices[7]._position.y = -halfHeight;
		_vertices[7]._position.z = -halfDepth;

		_vertices[8]._position.x = halfWidth;
		_vertices[8]._position.y = -halfHeight;
		_vertices[8]._position.z = -halfDepth;

		_vertices[9]._position.x = halfWidth;
		_vertices[9]._position.y = -halfHeight;
		_vertices[9]._position.z = -halfDepth;

		_vertices[10]._position.x = halfWidth;
		_vertices[10]._position.y = halfHeight;
		_vertices[10]._position.z = -halfDepth;

		_vertices[11]._position.x = -halfWidth;
		_vertices[11]._position.y = halfHeight;
		_vertices[11]._position.z = -halfDepth;

		for (unsigned int i = 6; i < 12; ++i)
		{
			_vertices[i]._normal = glm::vec3(0.0f, 0.0f, -1.0f);
			_vertices[i]._color = _color;
		}

		_vertices[12]._position.x = -halfWidth;
		_vertices[12]._position.y = halfHeight;
		_vertices[12]._position.z = halfDepth;

		_vertices[13]._position.x = -halfWidth;
		_vertices[13]._position.y = -halfHeight;
		_vertices[13]._position.z = halfDepth;

		_vertices[14]._position.x = -halfWidth;
		_vertices[14]._position.y = -halfHeight;
		_vertices[14]._position.z = -halfDepth;

		_vertices[15]._position.x = -halfWidth;
		_vertices[15]._position.y = -halfHeight;
		_vertices[15]._position.z = -halfDepth;

		_vertices[16]._position.x = -halfWidth;
		_vertices[16]._position.y = halfHeight;
		_vertices[16]._position.z = -halfDepth;

		_vertices[17]._position.x = -halfWidth;
		_vertices[17]._position.y = halfHeight;
		_vertices[17]._position.z = halfDepth;

		for (unsigned int i = 12; i < 18; ++i)
		{
			_vertices[i]._normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			_vertices[i]._color = _color;
		}

		_vertices[18]._position.x = halfWidth;
		_vertices[18]._position.y = halfHeight;
		_vertices[18]._position.z = -halfDepth;

		_vertices[19]._position.x = halfWidth;
		_vertices[19]._position.y = -halfHeight;
		_vertices[19]._position.z = -halfDepth;

		_vertices[20]._position.x = halfWidth;
		_vertices[20]._position.y = -halfHeight;
		_vertices[20]._position.z = halfDepth;

		_vertices[21]._position.x = halfWidth;
		_vertices[21]._position.y = -halfHeight;
		_vertices[21]._position.z = halfDepth;

		_vertices[22]._position.x = halfWidth;
		_vertices[22]._position.y = halfHeight;
		_vertices[22]._position.z = halfDepth;

		_vertices[23]._position.x = halfWidth;
		_vertices[23]._position.y = halfHeight;
		_vertices[23]._position.z = -halfDepth;

		for (unsigned int i = 18; i < 24; ++i)
		{
			_vertices[i]._normal = glm::vec3(1.0f, 0.0f, 0.0f);
			_vertices[i]._color = _color;
		}

		_vertices[24]._position.x = halfWidth;
		_vertices[24]._position.y = halfHeight;
		_vertices[24]._position.z = -halfDepth;

		_vertices[25]._position.x = halfWidth;
		_vertices[25]._position.y = halfHeight;
		_vertices[25]._position.z = halfDepth;

		_vertices[26]._position.x = -halfWidth;
		_vertices[26]._position.y = halfHeight;
		_vertices[26]._position.z = halfDepth;

		_vertices[27]._position.x = -halfWidth;
		_vertices[27]._position.y = halfHeight;
		_vertices[27]._position.z = halfDepth;

		_vertices[28]._position.x = -halfWidth;
		_vertices[28]._position.y = halfHeight;
		_vertices[28]._position.z = -halfDepth;

		_vertices[29]._position.x = halfWidth;
		_vertices[29]._position.y = halfHeight;
		_vertices[29]._position.z = -halfDepth;

		for (unsigned int i = 24; i < 30; ++i)
		{
			_vertices[i]._normal = glm::vec3(0.0f, 1.0f, 0.0f);
			_vertices[i]._color = _color;
		}

		_vertices[30]._position.x = halfWidth;
		_vertices[30]._position.y = -halfHeight;
		_vertices[30]._position.z = halfDepth;

		_vertices[31]._position.x = halfWidth;
		_vertices[31]._position.y = -halfHeight;
		_vertices[31]._position.z = -halfDepth;

		_vertices[32]._position.x = -halfWidth;
		_vertices[32]._position.y = -halfHeight;
		_vertices[32]._position.z = -halfDepth;

		_vertices[33]._position.x = -halfWidth;
		_vertices[33]._position.y = -halfHeight;
		_vertices[33]._position.z = -halfDepth;

		_vertices[34]._position.x = -halfWidth;
		_vertices[34]._position.y = -halfHeight;
		_vertices[34]._position.z = halfDepth;

		_vertices[35]._position.x = halfWidth;
		_vertices[35]._position.y = -halfHeight;
		_vertices[35]._position.z = halfDepth;

		for (unsigned int i = 30; i < 36; ++i)
		{
			_vertices[i]._normal = glm::vec3(0.0f, -1.0f, 0.0f);
			_vertices[i]._color = _color;
		}

		for (unsigned int i = 0; i < 36; ++i)
		{
			int modulo = i % 6;

			if (modulo == 0)
				_vertices[i]._texture = glm::vec2(1.0f, 0.0f);
			else if (modulo == 1)
				_vertices[i]._texture = glm::vec2(1.0f, 1.0f);
			else if (modulo == 2)
				_vertices[i]._texture = glm::vec2(0.0f, 1.0f);
			else if (modulo == 3)
				_vertices[i]._texture = glm::vec2(0.0f, 1.0f);
			else if (modulo == 4)
				_vertices[i]._texture = glm::vec2(0.0f, 0.0f);
			else if (modulo == 5)
				_vertices[i]._texture = glm::vec2(1.0f, 0.0f);

			_vertices[i]._transform = pos;
		}

	};
	~CUnitGraphicsComponent() {};

	void update(CUnit& unit, CRenderer& renderer);

private:
	glm::vec4 _color;
	GLuint _textureID;
	std::vector<Vertex> _vertices;

	BatchConfig _config;
};