#include <thread>
#include <iostream>

#include "Camera.h"
#include "PlayState.h"
#include "Renderer.h"
#include "Service.h"
#include "Unit.h"

void CPlayState::init()
{
	GLuint diffuseMap = CService::getRenderer()->loadTexture("res/container.png");
	GLuint specularMap = CService::getRenderer()->loadTexture("res/container_specular.png");

	for (int i = 0; i < 100; i++)
	{
		float x = (float)((rand() % 500 - 250) / 100.0);
		float y = (float)((rand() % 500 - 250) / 100.0);
		float z = (float)((rand() % 200) / 50.0);
		float w = (float)((rand() % 10 + 10) / 100.0);
		float h = (float)(w);
		//std::cout << "Unit: " << x << " " << y << " " << z << std::endl;
		float r, g, b, angle;
		r = (float)((rand() % 100) / 100.0);
		g = (float)((rand() % 100) / 100.0);
		b = (float)((rand() % 100) / 100.0);
		angle = (float)(rand() % 100);

		//std::cout << x << " " << y << " " << w << std::endl;
		_units.emplace_back(new CUnit(glm::vec3(x, y, z), glm::vec3(r, g, b), w, h, 0.003f, glm::vec4(r, g, b, 1.0f), diffuseMap));
	}
}

void CPlayState::cleanup()
{

}

void CPlayState::pause()
{

}

void CPlayState::resume()
{

}

void CPlayState::handleInput(CGame* game, int key, int action)
{
	if (key == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
		_lmbPressed = true;

	if (key == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
		_lmbPressed = false;

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (key == GLFW_KEY_C && action == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

	if (key == GLFW_KEY_W)
		CService::getCamera()->setDirection(FORWARD, action);
	if (key == GLFW_KEY_S)
		CService::getCamera()->setDirection(BACKWARD, action);
	if (key == GLFW_KEY_A)
		CService::getCamera()->setDirection(LEFT, action);
	if (key == GLFW_KEY_D)
		CService::getCamera()->setDirection(RIGHT, action);
}

void CPlayState::handleInput(CGame* game, double x, double y)
{
	/*if (_lmbPressed)
	{
		std::cout << "wcisniety!" << std::endl;
		_select[2] = (float)x;
		_select[3] = (float)(720 - y);
	}
	else
	{
		_select[0] = (float)x;
		_select[1] = (float)(720 - y);
		_select[2] = (float)x;
		_select[3] = (float)(720 - y);
	}
	if (_lmbPressed)
	{
		std::cout << "wcisniety!" << std::endl;
		_select[1]._position.x = (float)x;
		_select[1]._position.y = (float)(720 - y);
	}
	else
	{
		_select[0]._position.x = (float)x;
		_select[0]._position.y = (float)(720 - y);
		_select[1] = (float)x;
		_select[1] = (float)(720 - y);
	}*/
}

void CPlayState::update(CGame* game)
{
	CService::getCamera()->move();

	for (CUnit* u : _units)
	{
		u->update();

		/*if (u->_position.x >= _select[0] && u->_position.x <= _select[2] &&
				u->_position.y >= _select[1] && u->_position.y <= _select[3])
			_selectedUnits.push_back(u);*/
	}
}

void CPlayState::draw(CGame* game)
{
	CService::getRenderer()->clear();

	for (CUnit* u : _units)
		u->draw(*CService::getRenderer());

	drawSelectionRect();

	//CService::getRenderer()->render();
	CService::getRenderer()->emptyAllBatches();
	CService::getRenderer()->swapBuffers();
}

void CPlayState::drawSelectionRect()
{
	_select[0]._position.x = -3;
	_select[0]._position.y = 3;
	_select[0]._position.z = -4;

	_select[1]._position.x = 3;
	_select[1]._position.y = 3;
	_select[1]._position.z = -4;

	_select[2]._position.x = -3;
	_select[2]._position.y = -3;
	_select[2]._position.z = -4;

	_select[3]._position.x = 3;
	_select[3]._position.y = -3;
	_select[3]._position.z = -4;

	for (unsigned int i = 0; i < _select.size(); i++)
	{
		_select[i]._normal = glm::vec3(0.0f, 0.0f, 1.0f);
		_select[i]._color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	}
	CService::getRenderer()->render(_select, BatchConfig(GL_TRIANGLE_STRIP, 0, 0));
}

void CPlayState::setupLights()
{
	
}