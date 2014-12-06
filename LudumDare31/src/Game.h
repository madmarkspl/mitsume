#pragma once
#include <stack>

class CGameState;

class CGame
{
public:
	CGame() { _running = true; };
	~CGame() {};

	void changeState(CGameState* state);
	void pushState(CGameState* state);
	void popState();

	void handleEvents();
	void update();
	void draw(double extrapolation);

	void init();
	void cleanup();

	bool running() { return _running; }
	void quit() { _running = false;  }

private:
	std::stack<CGameState*> _stateStack;
	bool _running;

};
