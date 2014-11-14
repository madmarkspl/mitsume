#include "Game.h"
#include "GameState.h"

void CGame::init()
{

}

void CGame::cleanup()
{
	while (!_stateStack.empty())
	{
		_stateStack.top()->cleanup();
		_stateStack.pop();
	}
}

void CGame::changeState(CGameState* state)
{
	if (!_stateStack.empty())
	{
		_stateStack.top()->cleanup();
		_stateStack.pop();
	}

	_stateStack.push(state);
	_stateStack.top()->init();
}

void CGame::pushState(CGameState* state)
{
	if (!_stateStack.empty())
	{
		_stateStack.top()->pause();
	}
	_stateStack.push(state);
	_stateStack.top()->init();
}

void CGame::popState()
{
	if (!_stateStack.empty())
	{
		_stateStack.top()->cleanup();
		_stateStack.pop();
	}

	if (!_stateStack.empty())
	{
		_stateStack.top()->resume();
	}
}

void CGame::handleEvents()
{
	_stateStack.top()->handleInput(this);
}

void CGame::update()
{
	_stateStack.top()->update(this);
}

void CGame::draw(double extrapolation)
{
	_stateStack.top()->draw(this);
}
