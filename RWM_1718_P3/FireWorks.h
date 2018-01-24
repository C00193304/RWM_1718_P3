#pragma once
#include "GameObject.h"
#include "EventListener.h"
#include <vector>
#include "Box2D\Box2D.h"
#include "ExternalLibs\SDL2-2.0.7\include\SDL.h"
#include <string>
#include "World.h"

class Fireworks : public GameObject
{
private:
	struct Particle {
		b2Body* body;
		int expired;

		b2PolygonShape dynamicBox;

		b2BodyDef bodyDef;
		b2Vec2 velocity;

		Colour colour;

		SDL_Rect* m_rect;
		Size2D size;
	};
	int const MAXIMUM_PARTICLES = 1000;
	int const MAX_TIME = 100;

	std::vector<Particle> particles;

	void amountParticles(int amount);

	Particle ParentsParticles;

	b2Vec2 m_velocity;
	int particleAmount;

public:

	Fireworks() {};
	Fireworks(b2World*, int amount);
	~Fireworks();

	void Init(b2World* pWorld, int);
	void Update(unsigned int deltaTime);
	void Render(Renderer & r);

	void SetType(std::string t) { type = t; };
	std::string GetType() { return type; };
	b2Body * GetBody() { return ParentsParticles.body; };
};