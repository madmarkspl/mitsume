#include <iostream>
#include "Service.h"
#include "PlayState.h"
#include "Window.h"
#include "Unit.h"

void CPlayState::init()
{
	for (int i = 0; i < 1000; i++)
	{
		float x = (float)((rand() % 50) / 1200.0);
		float y = (float)((rand() % 50) / 700.0);
		float z = (float)(-1)*((rand() % 100) / 100.0);
		float w = (float)((rand() % 10 + 10) / 700.0);
		float h = (float)(w * (1280.0 / 720.0));

		float r, g, b;
		r = (float)((rand() % 100) / 100.0);
		g = (float)((rand() % 100) / 100.0);
		b = (float)((rand() % 100) / 100.0);
		//std::cout << x << " " << y << " " << w << std::endl;
		_units.push_back(new CUnit(glm::vec3(x, y, z), w, h, 0.003f, glm::vec4(r, g, b, 1.0)));
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
	CService::getGraphics()->clear();

	for (CUnit* u : _units)
		u->draw(*CService::getGraphics());

	drawSelectionRect();

	//CService::getGraphics()->render();
	CService::getGraphics()->emptyAllBatches();
	CService::getGraphics()->swapBuffers();
}

void CPlayState::drawSelectionRect()
{
	_select[0]._position.x = -3;
	_select[0]._position.y = 3;
	_select[0]._position.z = -5;

	_select[1]._position.x = 3;
	_select[1]._position.y = 3;
	_select[1]._position.z = -5;

	_select[2]._position.x = -3;
	_select[2]._position.y = -3;
	_select[2]._position.z = -5;

	_select[3]._position.x = 3;
	_select[3]._position.y = -3;
	_select[3]._position.z = -5;

	for (int i = 0; i < 4; i++)
	{
		_select[i]._color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	CService::getGraphics()->render(_select, BatchConfig(GL_TRIANGLE_STRIP, 0, 0));
}