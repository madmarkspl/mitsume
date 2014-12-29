#pragma once
#include <vector>
#include "GameState.h"
#include "Batch.h"

class CGame;
class CUnit;

class CPlayState : public CGameState
{
public:
	CPlayState() : _select(4) {}
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
	void setupLights();

	std::vector<CUnit*> _units;
	std::vector<CUnit*> _selectedUnits;
	std::vector<Vertex> _select;

	bool _lmbPressed;

};