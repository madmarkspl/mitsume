#pragma once
#include "Service.h"
class GameObject;

class InputComponent
{
public:
		virtual ~InputComponent() {}
		virtual void update(GameObject& obj /* level */) = 0;
};

class PhysicsComponent
{
public:
		virtual ~PhysicsComponent() {}
		virtual void update(GameObject& obj /* level */ ) = 0;
};

class GraphicsComponent
{
public:
		virtual ~GraphicsComponent() {}
		virtual void update(GameObject& obj, CWindow& graphics) = 0;
};

class AudioComponent
{
public:
		virtual ~AudioComponent() {}
		virtual void update(GameObject& obj, CWindow& graphics) = 0;
};
