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

void CIntroState::handleInput(CGame* game)
{
	
}

void CIntroState::update(CGame* game)
{
	//std::cout << "intro update" << std::endl;
}

void CIntroState::draw(CGame* game)
{
		
		CService::getGraphics(0)->clear();
		CService::getGraphics(0)->drawObject();
		CService::getGraphics(0)->render();

		CService::getGraphics(1)->clear();
		CService::getGraphics(1)->drawObject();
		CService::getGraphics(1)->render();
}
