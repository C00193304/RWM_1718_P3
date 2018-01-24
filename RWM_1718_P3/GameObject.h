#pragma once
#include <Box2D\Box2D.h>
#include "Renderer.h"
#include "Sprite.h"

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void Render(Renderer& r) = 0;
	virtual void Update(unsigned int deltaTime) = 0;
	virtual b2Body* GetBody() = 0;
	virtual void SetType(std::string t) = 0;
	virtual std::string GetType() = 0;


protected:

	std::string type;
};