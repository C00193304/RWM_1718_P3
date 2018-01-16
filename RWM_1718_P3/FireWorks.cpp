#include "FireWorks.h"

FireWork::FireWork()
{
	
	gravity = 9.81f;
	baseLineYSpeed = -4.0f;
	maxYSpeed = -4.0f;
}

void FireWork::init()
{
	float xLocation = ((float)rand() / (float)RAND_MAX) * 800.0f;
	float xSpeedValue  = -2 + ((float)rand() / (float)RAND_MAX) * 4.0f;
	float ySpeedValue = baseLineYSpeed + ((float)rand() / (float)RAND_MAX) * maxYSpeed;

	for (int i = 0; i < FIREWORK_PARTICLES; i++)
	{
		x[i] = xLocation;
		y[i] = 610.0f;
		xSpeed[i] = xSpeedValue;
		ySpeed[i] = ySpeedValue;
	}
	red = ((float)rand() / (float)RAND_MAX);
	green = ((float)rand() / (float)RAND_MAX);
	blue = ((float)rand() / (float)RAND_MAX);
	alpha = 1.0f;

	framesUntilLaunch = ((int)rand() % 400);

	particleSize = 1.0f + ((float)rand() / (float)RAND_MAX) * 3.0f;

	hasExploded = false;
}

void FireWork::move()
{
	for (int i = 0; i < FIREWORK_PARTICLES; i++)
	{
		if (framesUntilLaunch <= 0)
		{
			x[i] += xSpeed[i];
			y[i] += ySpeed[i];
			ySpeed[i] += gravity;
		}
	}
	framesUntilLaunch--;

	if (ySpeed[0] > 0.0f)
	{
		for (int i = 0; i < FIREWORK_PARTICLES; i++)
		{
			xSpeed[i] = -4 + (rand() / (float)RAND_MAX) * 8;
			ySpeed[i] = -4 + (rand() / (float)RAND_MAX) * 8;
		}
		hasExploded = true;
	}
}

void FireWork::explode()
{
	for (int i = 0; i < FIREWORK_PARTICLES; i++)
	{
		xSpeed[i] *= 0.99f;

		x[i] += xSpeed[i];
		y[i] += ySpeed[i];

		ySpeed[i] += gravity;
	}
	if (alpha > 0.0f)
	{
		alpha -= 0.01f;
	}
	else
	{
		init();
	}

}

void FireWork::update()
{
	for (int i = 0; i < FIREWORK_PARTICLES; i++)
	{
		if (hasExploded == true)
		{
			explode();
		}
	}
	move();

}

void FireWork::Draw()
{

}