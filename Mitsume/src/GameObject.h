#pragma once

class CInputComponent;
class CPhysicsComponent;
class CGraphicsComponent;

class CGameObject
{
public:
		CGameObject();
		~CGameObject();

private:
		CInputComponent* _input;
		CPhysicsComponent* _physics;
		CGraphicsComponent* _graphics;
};

