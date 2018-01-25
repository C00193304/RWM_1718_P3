#pragma once
#include <SDL.h>
#include <Box2D\Box2D.h>
#include <vector>
#include "BasicTypes.h"
#include "EventListener.h"
#include <time.h>
#include <random>

const int FIREWORKS_PARTICLES = 30000;
const int MAX_LIFE = 1000;

//create method that creates the generic firework in a position of your choice
//create a method that changes the colour you just give it an rgb value in int form between 1 and 255
//create a method that changes its life time of when the particles delte themselves.
//create a method that makes a firework of your choice into a sparkler instead of a rocket explosion
//make a set life method to set the life in miliseconds of the particle so it dies after that

namespace Particles
{

	class Fireworks
	{
	private:
		struct Particle
		{
			b2Body* body;
			b2BodyDef bodyDef;
			b2FixtureDef fixtureDef;
			b2PolygonShape dynamicBox;
			b2Vec2 velocity;
			Colour colour;
			int life;
			SDL_Rect* m_rect;
			int width;
			int height;
		};

		//enums for changing the type and colour
		enum Types
		{
			spaklervag,
			generic,
			cluster,
		};

		bool genericFireworks = false;
		bool sparklers = false;
		bool clusters = false;
		int fuelCount;
		
		std::vector<Particle> particles;

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

		void Fireworks::fuelParticles(int amount, int red, int green, int blue)
		{
			if (amount + particles.size() > FIREWORKS_PARTICLES)
			{
				amount = FIREWORKS_PARTICLES - particles.size();
			}

			for (int i = 0; i < amount; i++)
			{
				if (genericFireworks == true)
				{
					Particle temp;
					temp = Parent;
					float rX, rY;
					rX = ((rand() % 1000) - 500.f) / 0.5f;
					rY = ((rand() % 1000) - 500.f) / 0.5f;
					temp.velocity = b2Vec2(rX, rY);
					int r, g, b;
					r = red;
					g = green;
					b = blue;
					temp.colour = Colour(r, g, b, 255);
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
		}
		Particle Parent;
		b2World* worlds;
		b2Vec2 m_velocity;
	public:
		Fireworks() {};
		~Fireworks() {};

		void Fireworks::init(b2World* world)
		{
			worlds = world;
			Parent.bodyDef.type = b2_kinematicBody;
			m_velocity = b2Vec2(0, 0);
			Parent.bodyDef.linearVelocity = m_velocity;
			Parent.bodyDef.position.Set(400, 300);
			Parent.bodyDef.awake = false;
			Parent.body = world->CreateBody(&Parent.bodyDef);
			Parent.width = 1;
			Parent.height = 1;
			Parent.dynamicBox.SetAsBox(Parent.width, Parent.height);
			Parent.fixtureDef.shape = &Parent.dynamicBox;
			Parent.fixtureDef.density = 1.5f;
			Parent.fixtureDef.friction = 1.0f;
			Parent.body->CreateFixture(&Parent.fixtureDef);

			srand(time(NULL));
		}

		void Fireworks::Update(unsigned int deltaTime, int red, int green, int blue)
		{
			if (fuelCount >= 0)
			{
				fuelParticles(10, red, green, blue);
				fuelCount--;
			}
			for (int i = 0; i < particles.size(); i++)
			{
				particles.at(i).body->SetLinearVelocity(particles.at(i).velocity);

			}
		}
		void Fireworks::Render(SDL_Renderer &r)
		{
			for (int i = 0; i < particles.size(); i++)
			{
				SDL_Rect rect{ particles.at(i).body->GetPosition().x, particles.at(i).body->GetPosition().y, particles.at(i).width, particles.at(i).height };
				SDL_SetRenderDrawColor(&r, rand() % 255, rand() % 255, rand() % 255, rand() % 255);
				SDL_RenderFillRect(&r, &rect);
			}
		}
	};
}