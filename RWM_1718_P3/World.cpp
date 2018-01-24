#include "World.h"

World::World()
{
	gravity = b2Vec2(0.0f, 10.0f);
	GameWorld = new b2World(gravity);

	TimeStep = 1.0f / 60.f;
	VelocityIterations = 8;
	PositionIterations = 3;

	Complete = false;
}

void World::Init()
{
	gravity = b2Vec2(0.0f, 10.0f);
	GameWorld = new b2World(gravity);

	TimeStep = 1.0f / 60.f;
	VelocityIterations = 8;
	PositionIterations = 3;

	Complete = false;
}

void World::Update(vector<GameObject*>& GameObjects)
{
	GameWorld->Step(TimeStep, VelocityIterations, PositionIterations);

	for (b2Contact* Contact = GameWorld->GetContactList(); Contact; Contact = Contact->GetNext())
	{
		b2Body* a = Contact->GetFixtureA()->GetBody();
		GameObject* ObjectA = GetGameObject(GameObjects, a);

		b2Body* b = Contact->GetFixtureB()->GetBody();
		GameObject* ObjectB = GetGameObject(GameObjects, b);

		Collision(ObjectA, ObjectB);
	}
}

GameObject * World::GetGameObject(vector<GameObject*>& GameObjects, b2Body* body)
{
	for (int i = 0; i < GameObjects.size(); i++)
	{
		if (GameObjects.at(i)->GetBody() == body)
		{
			return GameObjects.at(i);
		}
	}

	return NULL;
}

void World::Collision(GameObject * A, GameObject * B)
{
	if (A == NULL || B == NULL)
	{
		return;
	}

	if (A->GetType() == "CannonBall" || B->GetType() == "CannonBall")
	{
		if (A->GetType() == "Ground" || B->GetType() == "Ground")
		{

		}
		if (A->GetType() == "Wall" || B->GetType() == "Wall")
		{

		}
		if (A->GetType() == "Goal" || B->GetType() == "Goal")
		{
			Complete = true;
		}
	}
}