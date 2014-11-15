#pragma once

class CWindow;
class CGameObject;
class CLevel;

class CInputComponent
{
public:
		virtual ~CInputComponent() {}
		virtual void update(CGameObject& obj) = 0;
};

class CPhysicsComponent
{
public:
		virtual ~CPhysicsComponent() {}
		virtual void update(CGameObject& obj, CLevel& level) = 0;
};

class CGraphicsComponent
{
public:
		virtual ~CGraphicsComponent() {}
		virtual void update(CGameObject& obj, CWindow& window) = 0;
};

class CAudioComponent
{
public:
		virtual ~CAudioComponent() {}
		virtual void update(CGameObject& obj) = 0;
};
