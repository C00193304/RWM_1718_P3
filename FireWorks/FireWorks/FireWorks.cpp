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
				rX = ((rand() % 100) - 10) / 0.5f;
				rY = ((rand() % 1500) - 1000) / 0.5f;
				/*temp.velocity = b2Vec2(rX, rY);*/
				int r, g, b;
				r = rand() % 255;
				g = rand() % 255;
				b = rand() % 255;
				temp.colour = Colour(r, g, b, 255);
				temp.width = temp.height = 1 + (rand() % 5);
				temp.life = 10;
				temp.bodyDef.awake = true;
				//temp.bodyDef.linearVelocity = temp.velocity;
				temp.body = worlds->CreateBody(&temp.bodyDef);
				temp.bodyDef.position.Set(temp.body->GetPosition().x, temp.body->GetPosition().y);
				particles.push_back(temp);
				temp.life--;
				if (temp.life <= MAX_LIFE)
				{
					particles.clear();
					particles.pop_back();
				}
			}
	}

	void Fireworks::init(b2World* world,int x, int y)
	{
		worlds = world;
		m_velocity = b2Vec2(((rand() % 100) - 1), -50.f);
		Parent.bodyDef.type = b2_kinematicBody;
		Parent.bodyDef.position.Set(x, y);
		//Parent.bodyDef.angularVelocity = 10;
		//Parent.body->ApplyLinearImpulse(b2Vec2(rand() % 100 - 1, -50.f) ,Parent.body->GetWorldCenter(), true);
		Parent.bodyDef.awake = false;
		Parent.body = world->CreateBody(&Parent.bodyDef);
		Parent.width = 1;
		Parent.height = 1;
		Parent.dynamicBox.SetAsBox(Parent.width, Parent.height);
		Parent.fixtureDef.shape = &Parent.dynamicBox;
		Parent.fixtureDef.density = 1.0f;
		Parent.fixtureDef.friction = 1.0f;
		Parent.body->CreateFixture(&Parent.fixtureDef);
		srand(time(NULL));
	}

	void Fireworks::Update()
	{
		if (fuelCount >= 0)
		{
			fuelParticles(100);
			fuelCount--;
		}
		//for (int i = 0; i < particles.size(); i++)
		//{
		//	particles.at(i).body->SetLinearVelocity(particles.at(i).velocity);
		//}
	}
	void Fireworks::Render(SDL_Renderer * r)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			SDL_Rect rect{ particles.at(i).body->GetPosition().x, particles.at(i).body->GetPosition().y, particles.at(i).width, particles.at(i).height };
			SDL_SetRenderDrawColor(r, rand() % 255, rand() % 255, rand() % 255, 255);
			SDL_RenderFillRect(r, &rect);
		}
	}
}