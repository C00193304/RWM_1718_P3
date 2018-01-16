#ifndef FIREWORKS_H
#define FIREWORKS_H

#include <iostream>
#include "Box2D\Box2D.h"
#include "ExternalLibs\SDL2-2.0.7\include\SDL.h"

const int FIREWORK_PARTICLES = 70;

class FireWork
{
public:
	float x[FIREWORK_PARTICLES];
	float y[FIREWORK_PARTICLES];
	float xSpeed[FIREWORK_PARTICLES];
	float ySpeed[FIREWORK_PARTICLES];

	float red;
	float blue;
	float green;
	float alpha;

	int framesUntilLaunch;
	float particleSize;
	bool hasExploded;
	
	float baseLineYSpeed;
	float maxYSpeed;

	float gravity;

	FireWork();
	void init();
	void move();
	void explode();
	void update();
	void Draw();
private:

};
#endif