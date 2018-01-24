#include "Fireworks.h"
#include <time.h>
#include<iostream>

Fireworks::Fireworks(b2World* pWorld , int amount)
{
	m_velocity = b2Vec2(0, 0);

	// Body Definition
	ParentsParticles.bodyDef.type = b2_kinematicBody;
	ParentsParticles.bodyDef.linearVelocity = m_velocity;
	ParentsParticles.bodyDef.position.Set(100,100);//random values
	ParentsParticles.bodyDef.awake = false;
	ParentsParticles.body = pWorld->CreateBody(&ParentsParticles.bodyDef);

	// Set Size of particles
	ParentsParticles.size.w = 5;
	ParentsParticles.size.h = 5;

	ParentsParticles.dynamicBox.SetAsBox(ParentsParticles.size.w, ParentsParticles.size.h);

	ParentsParticles.body->CreateFixture(&ParentsParticles.dynamicBox, 0);

	if (amount + particles.size() > MAXIMUM_PARTICLES)
	{
		amount = MAXIMUM_PARTICLES - particles.size();
	}
	for (int i = 0; i < amount; i++)
	{
		Particle tempParticle;
		tempParticle = ParentsParticles;

		float renderX, renderY;
		renderX = ((rand() % 1000) - 500.f) / 0.5f;
		renderY = ((rand() % 1000) - 500.f) / 0.5f;
		renderY = (rand() % 10 - 70);// / 0.5f;
		tempParticle.velocity = b2Vec2((rand() % 2), renderY);
		int red, green, blue;

		red = 255;
		green = 255;
		blue = 255;
		tempParticle.colour = Colour(red, green, blue, rand() % 155);
		tempParticle.size.w = tempParticle.size.h = 1 + (rand() % 5);
		tempParticle.expired = 1;
		tempParticle.bodyDef.awake = true;
		tempParticle.bodyDef.linearVelocity = tempParticle.velocity;
		tempParticle.body = pWorld->CreateBody(&tempParticle.bodyDef);
		particles.push_back(tempParticle);
	}
}

Fireworks::~Fireworks() {}

void Fireworks::Init(b2World* pWorld, int amount)
{
	if (amount + particles.size() > MAXIMUM_PARTICLES)
	{
		amount = MAXIMUM_PARTICLES - particles.size();
	}
	for (int i = 0; i < amount; i++)
	{
		Particle tempParticle;
		tempParticle = ParentsParticles;

		float renderX, renderY;
		renderX = ((rand() % 1000) - 500.f) / 0.5f;
		renderY = ((rand() % 1000) - 500.f) / 0.5f;
		renderY = (rand() % 10 - 70);// / 0.5f;
		tempParticle.velocity = b2Vec2((rand() % 2), renderY);
		int red, green, blue;

		red = 255;
		green = 255;
		blue = 255;
		tempParticle.colour = Colour(red, green, blue, rand() % 155);
		tempParticle.size.w = tempParticle.size.h = 1 + (rand() % 5);
		tempParticle.expired = 1;
		tempParticle.bodyDef.awake = true;
		tempParticle.bodyDef.linearVelocity = tempParticle.velocity;
		tempParticle.body = pWorld->CreateBody(&tempParticle.bodyDef);
		particles.push_back(tempParticle);
	}
}

void Fireworks::Update(unsigned int deltaTime)
{
	if (particleAmount >= 0)
	{
		amountParticles(1);
		particleAmount--;
	}
	for (int i = 0; i < particles.size(); i++)
	{
		particles.at(i).body->SetLinearVelocity(particles.at(i).velocity);
	}
}
void Fireworks::Render(Renderer & r)
{
	for (int i = 0; i < particles.size(); i++)
	{
		Rect rect(particles.at(i).body->GetPosition().x, particles.at(i).body->GetPosition().y, particles.at(i).size.w, particles.at(i).size.h);
		r.drawRect(rect, particles.at(i).colour);
	}
}

void Fireworks::amountParticles(int amount)
{
	b2World* world;
	if (amount + particles.size() > MAXIMUM_PARTICLES)
	{
	amount = MAXIMUM_PARTICLES - particles.size();
	}
	for (int i = 0; i < amount; i++)
	{
	Particle tempParticle;
	tempParticle = ParentsParticles;

	float renderX, renderY;
	renderX = ((rand() % 1000) - 500.f) / 0.5f;
	renderY = ((rand() % 1000) - 500.f) / 0.5f;
	tempParticle.velocity = b2Vec2(renderX, renderY);
	int red, green, blue;

	red = 255;
	green = 255;
	blue = 255;
	tempParticle.colour = Colour(red, green, blue, rand() % 255 + 1);
	tempParticle.size.w = tempParticle.size.h = 1 + (rand() % 5);
	tempParticle.expired = MAX_TIME;
	tempParticle.bodyDef.awake = true;
	tempParticle.bodyDef.linearVelocity = tempParticle.velocity;
	tempParticle.body = world->CreateBody(&tempParticle.bodyDef);
	particles.push_back(tempParticle);
	}
}