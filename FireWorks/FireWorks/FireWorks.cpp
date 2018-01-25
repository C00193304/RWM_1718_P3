#include "FireWorks.h"
namespace Particles
{
	void Fireworks::onEvent(EventListener::Event evt)
	{
		switch (evt)
		{
		case EventListener::FUEL:
			fuelCount = 100;
			break;
		default:
			break;
		}

	}

	void Fireworks::fuelParticles(int amount)
	{
		if (amount + particles.size() > FIREWORKS_PARTICLES)
		{
			amount = FIREWORKS_PARTICLES - particles.size();
		}

		for (int i = 0; i < amount; i++)
		{
				Particle temp;
				temp = Parent;
				float rX, rY;
				rX = ((rand() % 1000) - 500.f) / 0.5f;
				rY = ((rand() % 1000) - 500.f) / 0.5f;
				temp.velocity = b2Vec2(rX, rY);
				temp.colour = Colour(255, 255, 255, 255);
				temp.width = temp.height = 1 + (rand() % 5);
				temp.life = MAX_LIFE;
				temp.bodyDef.awake = true;
				temp.bodyDef.linearVelocity = temp.velocity;
				temp.body = worlds->CreateBody(&temp.bodyDef);
				particles.push_back(temp);
				temp.life--;
				if (temp.life <= 0)
				{
					particles.clear();
				}
			}
	}

	Fireworks::Fireworks(b2World* world, int amount, int x, int y, int fuelAmount)
	{
		m_velocity = b2Vec2(0, 0);

		// Body Definition
		Parent.bodyDef.type = b2_kinematicBody;
		Parent.bodyDef.linearVelocity = m_velocity;
		Parent.bodyDef.position.Set(x, y);
		Parent.bodyDef.awake = false;
		Parent.body = world->CreateBody(&Parent.bodyDef);

		// Set Size of particles
		Parent.width = 5;
		Parent.height = 5;

		Parent.dynamicBox.SetAsBox(Parent.width, Parent.height);

		Parent.body->CreateFixture(&Parent.dynamicBox, 0);

		if (amount + particles.size() > FIREWORKS_PARTICLES)
		{
			amount = FIREWORKS_PARTICLES - particles.size();
		}
		for (int i = 0; i < amount; i++)
		{
			Particle tempParticle;
			tempParticle = Parent;

			float renderX, renderY;
			renderX = ((rand() % 1000) - 500.f) / 0.5f;
			renderY = ((rand() % 1000) - 500.f) / 0.5f;
			tempParticle.velocity = b2Vec2((rand() % 2), renderY);
			int red, green, blue;
			red = 255;
			green = 255;
			blue = 255;
			tempParticle.colour = Colour(red, green, blue, 255);
			tempParticle.width = tempParticle.height = 1 + (rand() % 5);
			tempParticle.expired = 1;
			tempParticle.bodyDef.awake = true;
			tempParticle.bodyDef.linearVelocity = tempParticle.velocity;
			tempParticle.body = world->CreateBody(&tempParticle.bodyDef);
			particles.push_back(tempParticle);
			fuelCount = fuelAmount;
		}
	}

	//void Fireworks::init(b2World* world)
	//{
	//	worlds = world;
	//	Parent.bodyDef.type = b2_kinematicBody;
	//	m_velocity = b2Vec2(0, 0);
	//	Parent.bodyDef.linearVelocity = m_velocity;
	//	Parent.bodyDef.position.Set(400, 300);
	//	Parent.bodyDef.awake = false;
	//	Parent.body = world->CreateBody(&Parent.bodyDef);
	//	Parent.width = 1;
	//	Parent.height = 1;
	//	Parent.dynamicBox.SetAsBox(Parent.width, Parent.height);
	//	Parent.fixtureDef.shape = &Parent.dynamicBox;
	//	Parent.fixtureDef.density = 1.5f;
	//	Parent.fixtureDef.friction = 1.0f;
	//	Parent.body->CreateFixture(&Parent.fixtureDef);

	//	srand(time(NULL));
	//}

	void Fireworks::Update()
	{
		if (fuelCount >= 0)
		{
			fuelParticles(100);
			fuelCount--;
		}
		for (int i = 0; i < particles.size(); i++)
		{
			particles.at(i).body->SetLinearVelocity(particles.at(i).velocity);
		}
	}
	void Fireworks::Render(SDL_Renderer * r)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			SDL_Rect rect{ particles.at(i).body->GetPosition().x, particles.at(i).body->GetPosition().y, particles.at(i).width, particles.at(i).height };
			SDL_SetRenderDrawColor(r, rand() % 255, rand() % 255, rand() % 255, rand() % 255);
			SDL_RenderFillRect(r, &rect);
		}
	}
}