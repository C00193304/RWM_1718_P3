#pragma once
#include <SDL.h>
#include <Box2D\Box2D.h>
#include <vector>
#include "BasicTypes.h"
#include "EventListener.h"
#include "Renderer.h"

const int FIREWORKS_PARTICLES = 1000;
const int MAX_LIFE = 1000;
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
	int fuelCount;
	std::vector<Particle> particles;
	void onEvent(EventListener::Event evt);
	void fuelParticles(int amount);
	Particle Parent;
	b2World* worlds;
	b2Vec2 m_velocity;
public:
	Fireworks();
	~Fireworks();
	void init(b2World* world);
	void Update(unsigned int deltaTime); 
	void Render(Renderer &r);
};