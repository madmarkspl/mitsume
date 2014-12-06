#include "GameObject.h"
#include "Components.h"

CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::update(CLevel& level, CWindow& window)
{
	_input->update(*this);
	_physics->update(*this, level);
	_graphics->update(*this, window);
	_audio->update(*this);
}