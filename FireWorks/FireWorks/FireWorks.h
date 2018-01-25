#pragma once
#include <SDL.h>
#include <Box2D\Box2D.h>
#include <vector>
#include "BasicTypes.h"
#include "EventListener.h"
#include <time.h>
#include <random>



//create method that creates the generic firework in a position of your choice
//create a method that changes the colour you just give it an rgb value in int form between 1 and 255
//create a method that changes its life time of when the particles delte themselves.
//create a method that makes a firework of your choice into a sparkler instead of a rocket explosion
//make a set life method to set the life in miliseconds of the particle so it dies after that
const int FIREWORKS_PARTICLES = 100;
const int MAX_LIFE = 1000;

namespace Particles
{

	class Fireworks
	{
	private:
		struct Particle
		{
			b2Body* body;
			int expired;
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


		int fuelCount;
		
		std::vector<Particle> particles;

		Particle Parent;
		b2World* worlds;
		b2Vec2 m_velocity;

	public:
		Fireworks() {};
		Fireworks(b2World*, int amount, int x, int y, int fuelAmount);
		~Fireworks() {};

		//void Fireworks::init(b2World* world);
		void Fireworks::onEvent(EventListener::Event evt);
		void Fireworks::fuelParticles(int amount);
		void Fireworks::Update();
		void Fireworks::Render(SDL_Renderer * r);

		b2Body * GetBody() { return Parent.body; };
		//SDL_Rect * GetRect() { return Parent.m_rect; }
	};
}