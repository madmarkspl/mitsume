#include <iostream>
#include "Service.h"
#include "IntroState.h"
#include "Window.h"

void CIntroState::init()
{

}

void CIntroState::cleanup()
{

}

void CIntroState::pause()
{

}

void CIntroState::resume()
{

}

void CIntroState::handleInput(CGame* game, int key, int action)
{
	
}

void CIntroState::handleInput(CGame* game, double x, double y)
{

}

void CIntroState::update(CGame* game)
{
	//std::cout << "intro update" << std::endl;
}

void CIntroState::draw(CGame* game)
{
		
	CService::getGraphics()->clear();
	GLfloat vertices[] = {
		0.0f, 0.0f, // Vertex 1 (X, Y)
		0.0f, 2.0f,  // Vertex 2 (X, Y)
		2.0f, 2.0f, // Vertex 3 (X, Y)

		0.0f, 0.0f, // Vertex 4 (X, Y)
		2.0f, 2.0f, // Vertex 5 (X, Y)
		2.0f, 0.0f  // Vertex 6 (X, Y)
	};
	//CService::getGraphics()->drawObject("basic", GL_TRIANGLE_FAN, vertices, sizeof(vertices), glm::vec4(1.0, 0.0, 1.0, 0.5));
	CService::getGraphics()->render();
}
