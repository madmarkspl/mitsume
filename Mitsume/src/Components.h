#pragma once
#include "Service.h"
class GameObject;

class CInputComponent
{
public:
		virtual ~CInputComponent() {}
		virtual void update(GameObject& obj /* level */) = 0;
};

class CPhysicsComponent
{
public:
		virtual ~CPhysicsComponent() {}
		virtual void update(GameObject& obj /* level */ ) = 0;
};

class CGraphicsComponent
{
public:
		virtual ~CGraphicsComponent() {}
		virtual void update(GameObject& obj, CWindow& graphics) = 0;
};

class CAudioComponent
{
public:
		virtual ~CAudioComponent() {}
		virtual void update(GameObject& obj, CWindow& graphics) = 0;
};
