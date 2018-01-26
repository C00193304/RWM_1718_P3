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

				temp.width = temp.height = 1 + (rand() % 5);
				temp.life = 10;
				temp.bodyDef.awake = true;
				temp.body = worlds->CreateBody(&temp.bodyDef);
				temp.bodyDef.position.Set(temp.body->GetPosition().x + m_velocity.x, temp.body->GetPosition().y + m_velocity.y);
				particles.push_back(temp);

				particles.at(i).body->SetLinearVelocity(b2Vec2(Parent.body->GetLinearVelocity().x + ((rand() % 500) - 250), Parent.body->GetLinearVelocity().y + ((rand() % 500) - 250)));
			}
	}

	void Fireworks::setColourRed()
	{
		Parent.colour.r = (rand() % 230) + 25;
		Parent.colour.g = 0;
		Parent.colour.b = 0;
	}

	void Fireworks::setColourGreen()
	{
		Parent.colour.r = 0;
		Parent.colour.g = (rand() % 230 + 25);
		Parent.colour.b = 0;
	}

	void Fireworks::setColourBlue()
	{
		Parent.colour.r = 0;
		Parent.colour.g = 0;
		Parent.colour.b = (rand() % 230) + 25;
	}

	void Fireworks::init(b2World* world, int x, int y)
	{
		Parent.life = 150;
		fuelCount = 50;
		worlds = world;
		m_velocity = b2Vec2(50, -50.f);
		Parent.bodyDef.type = b2_kinematicBody;
		Parent.bodyDef.position.Set(x, y);
		Parent.bodyDef.angularVelocity = 10;
		Parent.bodyDef.awake = true;
		Parent.body = world->CreateBody(&Parent.bodyDef);
		Parent.width = 1;
		Parent.height = 1;
		Parent.dynamicBox.SetAsBox(Parent.width, Parent.height);
		Parent.fixtureDef.shape = &Parent.dynamicBox;
		Parent.fixtureDef.density = 1.0f;
		Parent.body->CreateFixture(&Parent.fixtureDef);
		Parent.body->ApplyLinearImpulseToCenter(m_velocity, true);
		srand(time(NULL));
		Parent.body->SetLinearVelocity(b2Vec2((rand() % 1000) - 500, (rand() % 1000) - 500));
	}

	void Fireworks::Update()
	{
		Parent.life--;

		if (Parent.life <= 0)
		{
			for (int i = 0; i < particles.size(); i++)
			{
				particles.erase(particles.begin() + i);
			}
			particles.shrink_to_fit();
		}
		if (fuelCount >= 0)
		{
			fuelParticles(50);
			fuelCount--;
			//std::cout << Parent.velocity.x << std::endl;
		}
		for (int i = 0; i < particles.size(); i++)
		{
			particles.at(i).body->SetLinearVelocity(b2Vec2(particles.at(i).body->GetLinearVelocity().x* 0.99, particles.at(i).body->GetLinearVelocity().y + (9.81 / 100)));
		}
	}
	void Fireworks::Render(SDL_Renderer * r)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			SDL_Rect rect{ particles.at(i).body->GetPosition().x, particles.at(i).body->GetPosition().y, particles.at(i).width, particles.at(i).height };
			SDL_SetRenderDrawColor(r, Parent.colour.r, Parent.colour.g, Parent.colour.b, Parent.colour.a);
			SDL_RenderFillRect(r, &rect);
		}
	}
}