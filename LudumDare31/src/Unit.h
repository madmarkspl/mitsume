#pragma once
#include <glm/glm.hpp>
#include "Components.h"

class CUnit
{
	friend class CUnitGraphicsComponent;
	friend class CUnitInputComponent;
public:
	CUnit(glm::vec2 position, float width, float height, float velocity, glm::vec4 color);

	~CUnit();

	void input();
	void update();
	void draw(CWindow& window);

private:
	glm::vec2 _position;
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
	glm::vec2 _moveVector;
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
	CUnitGraphicsComponent(glm::vec2 pos, float width, float height, glm::vec4 color) : _color(color)
	{
		

		/*_vertices[8] = pos.x + widthHalved;
		_vertices[9] = pos.y + heightHalved;

		_vertices[10] = pos.x + widthHalved;
		_vertices[11] = pos.y - heightHalved;*/

		/*_vertices = new float[12]
		{

				pos.x - widthHalved, pos.y + heightHalved,
				pos.x + widthHalved, pos.y - heightHalved,
				pos.x - widthHalved, pos.y - heightHalved,

				pos.x - widthHalved, pos.y + heightHalved,
				pos.x + widthHalved, pos.y + heightHalved,
				pos.x + widthHalved, pos.y - heightHalved
		};*/

	};
	~CUnitGraphicsComponent() {};

	void update(CUnit& unit, CWindow& window);

private:
	glm::vec4 _color;
	float _vertices[8];
};