#pragma once

class CWindow;
class CUnit;
class CLevel;

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

class CHealthComponent
{
public:
	virtual ~CHealthComponent() {}
	virtual void update(CUnit& obj) = 0;
};

class CGraphicsComponent
{
public:
		virtual ~CGraphicsComponent() {}
		virtual void update(CUnit& obj, CWindow& window) = 0;
};

class CAudioComponent
{
public:
		virtual ~CAudioComponent() {}
		virtual void update(CUnit& obj) = 0;
};
