#include <iostream>
#include "Service.h"
#include "PlayState.h"
#include "Window.h"
#include "Unit.h"

void CPlayState::init()
{
	for (int i = 0; i < 10; i++)
	{
		int x = rand() % 1200;
		int y = rand() % 700;
		int w = rand() % 10 + 10;
		int h = w;//rand() % 40 + 10;

		float r, g, b;
		r = (rand() % 100) / 100.0;;
		g = (rand() % 100) / 100.0;
		b = (rand() % 100) / 100.0;
		_units.push_back(new CUnit(glm::vec2(x, y), w, h, 1, glm::vec4(r, g, b, 1.0)));
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
	if (_lmbPressed)
	{
		std::cout << "wcisniety!" << std::endl;
		_select[2] = x;
		_select[3] = 720-y;
	}
	else
	{
		_select[0] = x;
		_select[1] = 720-y;
		_select[2] = x;
		_select[3] = 720-y;
	}

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

	CService::getGraphics()->render();
}

void CPlayState::drawSelectionRect()
{
	GLfloat vertices[] = {
		_select[0], _select[1],
		_select[2], _select[1],
		_select[2], _select[3],
		_select[0], _select[3],
	};
	CService::getGraphics()->drawObject(vertices, sizeof(vertices), glm::vec4(0.8, 1.0, 0.8, 1.0), GL_LINE_LOOP);
}