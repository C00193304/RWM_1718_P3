#pragma once
#include "stdafx.h"
#include <Box2D\Box2D.h>
#include "GameObject.h"

class World
{
private:
	b2Vec2 gravity;
	b2World * GameWorld;
	float TimeStep;
	int32 VelocityIterations;
	int32 PositionIterations;
	bool Complete;

public:
	World();

	~World() {};

	void Init();

	void Update(vector<GameObject*>& GameObjects);

	void Collision(GameObject*, GameObject*);

	GameObject * GetGameObject(vector<GameObject*>& GameObjects, b2Body* body);

	b2World * getWorld() { return GameWorld; };

	bool getLevelComplete() { return Complete; };
};