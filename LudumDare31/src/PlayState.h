#pragma once
#include <vector>
#include "GameState.h"

class CGame;
class CUnit;

class CPlayState : public CGameState
{
public:
	void init();
	void cleanup();

	void pause();
	void resume();

	void handleInput(CGame* game, int key, int action);
	void handleInput(CGame* game, double x, double y);
	void update(CGame* game);
	void draw(CGame* game);

private:
	void drawSelectionRect();

	std::vector<CUnit*> _units;
	std::vector<CUnit*> _selectedUnits;
	float _select[4];

	bool _lmbPressed;

};