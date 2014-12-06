#pragma once
#include "GameState.h"

class CGame;

class CIntroState : public CGameState
{
public:
	void init();
	void cleanup();

	void pause();
	void resume();

	void handleInput(CGame* game);
	void update(CGame* game);
	void draw(CGame* game);
	
};

