#pragma once

class CWindow;
class CUnit;
class CLevel;

class CAudioComponent
{
public:
	virtual ~CAudioComponent() {}
	virtual void update(CUnit& obj) = 0;
};

class CGraphicsComponent
{
public:
	virtual ~CGraphicsComponent() {}
	virtual void update(CUnit& obj, CRenderer& renderer) = 0;
};

class CHealthComponent
{
public:
	virtual ~CHealthComponent() {}
	virtual void update(CUnit& obj) = 0;
};

class CInputComponent
{
public:
		virtual ~CInputComponent() {}
		virtual void update(CUnit& obj) = 0;
};

class CPhysicsComponent
{
public:
		virtual ~CPhysicsComponent() {}
		virtual void update(CUnit& obj) = 0;
};

class CTransformComponent
{
public:
	virtual ~CTransformComponent() {}
	virtual void update(CUnit& obj) = 0;
};