#pragma once

class CWindow;
class CLevel;
class CInputComponent;
class CPhysicsComponent;
class CGraphicsComponent;
class CAudioComponent;

class CGameObject
{
public:
	CGameObject();
	~CGameObject();

	void update(CLevel& level, CWindow& window);

private:
	CInputComponent* _input;
	CPhysicsComponent* _physics;
	CGraphicsComponent* _graphics;
	CAudioComponent* _audio;
};

