#include "Renderer.h"
#include "Unit.h"
#include "Window.h"

CUnit::CUnit(glm::vec3 position, glm::vec3 rotation, float width, float height, float velocity, glm::vec4 color, GLuint textureID)
{
	_position = position;
	_rotation = rotation;
	_width = width;
	_height = height;
	_velocity = velocity;

	_input = new CUnitInputComponent();
	_physics = new CUnitPhysicsComponent();
	_health = new CUnitHealthComponent();
	_graphics = new CUnitGraphicsComponent(position, rotation, width, height, color, textureID);
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

void CUnit::draw(CRenderer& renderer)
{
	_graphics->update(*this, renderer);
}

void CUnitInputComponent::update(CUnit& unit)
{
	if (rand() % 100 > 98)
	{
		_moveVector = glm::normalize(glm::vec3((rand() % 100) / 50.0 - 1, (rand() % 100) / 50.0 - 1, (rand() % 100) / 50.0 - 1));
	}

	unit._position += _moveVector*unit._velocity;
	
	if (unit._position.x - unit._width / 2 <= -2 || unit._position.x + unit._width / 2 >= 2)
		unit._position.x -= _moveVector.x*unit._velocity;

	if (unit._position.y - unit._height / 2 <= -2 || unit._position.y + unit._height / 2 >= 2)
		unit._position.y -= _moveVector.y*unit._velocity;

	if (unit._position.z <= -3 || unit._position.z >= 0)
		unit._position.z -= _moveVector.z*unit._velocity;
}

void CUnitPhysicsComponent::update(CUnit& unit)
{

}

void CUnitHealthComponent::update(CUnit& unit)
{

}

void CUnitGraphicsComponent::update(CUnit& unit, CRenderer& renderer)
{
	for (unsigned int i = 0; i < 36; ++i)
		_vertices[i]._transform = unit._position;

	//static glm::mat4 identity;
	//_config._transformMatrix = glm::translate(identity, unit._position);
	//_config._transformMatrix = glm::rotate(_config._transformMatrix, unit._rotation.w, (glm::vec3)unit._rotation);

	renderer.render(_vertices, _config);
}

/*
_vertices[0]._position.x = unit._position.x - halfWidth;
_vertices[0]._position.y = unit._position.y + halfHeight;
_vertices[0]._position.z = unit._position.z;

_vertices[1]._position.x = unit._position.x + halfWidth;
_vertices[1]._position.y = unit._position.y + halfHeight;
_vertices[1]._position.z = unit._position.z;

_vertices[2]._position.x = unit._position.x - halfWidth;
_vertices[2]._position.y = unit._position.y - halfHeight;
_vertices[2]._position.z = unit._position.z;

_vertices[3]._position.x = unit._position.x + halfWidth;
_vertices[3]._position.y = unit._position.y - halfHeight;
_vertices[3]._position.z = unit._position.z;
*/

/*
_horizontalVertices[0]._position.x = halfWidth;
_horizontalVertices[0]._position.y = halfHeight;
_horizontalVertices[0]._position.z = halfDepth;

_horizontalVertices[1]._position.x = halfWidth;
_horizontalVertices[1]._position.y = -halfHeight;
_horizontalVertices[1]._position.z = halfDepth;

_horizontalVertices[2]._position.x = -halfWidth;
_horizontalVertices[2]._position.y = halfHeight;
_horizontalVertices[2]._position.z = halfDepth;

_horizontalVertices[3]._position.x = -halfWidth;
_horizontalVertices[3]._position.y = -halfHeight;
_horizontalVertices[3]._position.z = halfDepth;

//for (unsigned int i = 0; i < 4; ++i)
//	_horizontalVertices[0]._normal = glm::vec3(0.0f, 0.0f, 1.0f);

_horizontalVertices[4]._position.x = -halfWidth;
_horizontalVertices[4]._position.y = halfHeight;
_horizontalVertices[4]._position.z = -halfDepth;

_horizontalVertices[5]._position.x = -halfWidth;
_horizontalVertices[5]._position.y = -halfHeight;
_horizontalVertices[5]._position.z = -halfDepth;

_horizontalVertices[6]._position.x = halfWidth;
_horizontalVertices[6]._position.y = halfHeight;
_horizontalVertices[6]._position.z = -halfDepth;

_horizontalVertices[7]._position.x = halfWidth;
_horizontalVertices[7]._position.y = -halfHeight;
_horizontalVertices[7]._position.z = -halfDepth;


for (unsigned int i = 0; i < _horizontalVertices.size(); i++)
{
_horizontalVertices[i]._color = _color;
}

window.render(_horizontalVertices, _config);

_verticalVertices[0]._position.x = -halfWidth;
_verticalVertices[0]._position.y = -halfHeight;
_verticalVertices[0]._position.z = halfDepth;

_verticalVertices[1]._position.x = -halfWidth;
_verticalVertices[1]._position.y = -halfHeight;
_verticalVertices[1]._position.z = -halfDepth;

_verticalVertices[2]._position.x = halfWidth;
_verticalVertices[2]._position.y = -halfHeight;
_verticalVertices[2]._position.z = halfDepth;

_verticalVertices[3]._position.x = halfWidth;
_verticalVertices[3]._position.y = -halfHeight;
_verticalVertices[3]._position.z = -halfDepth;

_verticalVertices[4]._position.x = halfWidth;
_verticalVertices[4]._position.y = halfHeight;
_verticalVertices[4]._position.z = halfDepth;

_verticalVertices[5]._position.x = halfWidth;
_verticalVertices[5]._position.y = halfHeight;
_verticalVertices[5]._position.z = -halfDepth;

_verticalVertices[6]._position.x = -halfWidth;
_verticalVertices[6]._position.y = halfHeight;
_verticalVertices[6]._position.z = halfDepth;

_verticalVertices[7]._position.x = -halfWidth;
_verticalVertices[7]._position.y = halfHeight;
_verticalVertices[7]._position.z = -halfDepth;

for (unsigned int i = 0; i < _verticalVertices.size(); i++)
{
_verticalVertices[i]._color = _color;
}

window.render(_verticalVertices, _config);
*/