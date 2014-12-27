#include "Window.h"
#include "Unit.h"

CUnit::CUnit(glm::vec3 position, float width, float height, float velocity, glm::vec4 color)
{
	_position = position;
	_width = width;
	_height = height;
	_velocity = velocity;

	_input = new CUnitInputComponent();
	_physics = new CUnitPhysicsComponent();
	_health = new CUnitHealthComponent();
	_graphics = new CUnitGraphicsComponent(position, width, height, color);
}

CUnit::~CUnit()
{

}

void CUnit::update()
{
	_input->update(*this);
	_physics->update(*this);
	//_audio->update(*this);
}

void CUnit::draw(CWindow& window)
{
	_graphics->update(*this, window);
}

void CUnitInputComponent::update(CUnit& unit)
{
	if (rand() % 100 > 98)
	{
		_moveVector = glm::normalize(glm::vec3((rand() % 100) / 50.0 - 1, (rand() % 100) / 50.0 - 1, 0.0f));
	}

	unit._position += _moveVector*unit._velocity;
	
	if (unit._position.x - unit._width / 2 <= -1 || unit._position.x + unit._width / 2 >= 1)
		unit._position.x -= _moveVector.x*unit._velocity;

	if (unit._position.y - unit._height / 2 <= -1 || unit._position.y + unit._height / 2 >= 1)
		unit._position.y -= _moveVector.y*unit._velocity;
}

void CUnitPhysicsComponent::update(CUnit& unit)
{

}

void CUnitHealthComponent::update(CUnit& unit)
{

}

void CUnitGraphicsComponent::update(CUnit& unit, CWindow& window)
{
	float widthHalved = unit._width / 2;
	float heightHalved = unit._height / 2;

	_vertices[0]._position.x = unit._position.x - widthHalved;
	_vertices[0]._position.y = unit._position.y + heightHalved;
	_vertices[0]._position.z = unit._position.z;

	_vertices[1]._position.x = unit._position.x + widthHalved;
	_vertices[1]._position.y = unit._position.y + heightHalved;
	_vertices[1]._position.z = unit._position.z;

	_vertices[2]._position.x = unit._position.x - widthHalved;
	_vertices[2]._position.y = unit._position.y - heightHalved;
	_vertices[2]._position.z = unit._position.z;

	_vertices[3]._position.x = unit._position.x + widthHalved;
	_vertices[3]._position.y = unit._position.y - heightHalved;
	_vertices[3]._position.z = unit._position.z;


	for (int i = 0; i < 4; i++)
	{
		_vertices[i]._color = _color;
	}

	window.render(_vertices, _config);
}