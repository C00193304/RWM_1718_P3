#define SDL_MAIN_HANDLED

#include <iostream>
#include "SDL.h"
#include <Box2D\Box2D.h>
#include <time.h>
#include "FireWorks.h"
#include <random>
#include <vector>
#include "EventListener.h"
#include "BasicTypes.h"
#include <stdio.h>
#include <chrono>

int main(int argc, char* args[])
{
	bool quit = false;
	SDL_Event e;


	b2World* world;
	SDL_Renderer * renderer;
	SDL_Window* window = SDL_CreateWindow("fireworks!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	world = new b2World(b2Vec2(0.0, 9.81f));
	world->SetGravity(b2Vec2(0.0f, 9.81f));

	Particles::Fireworks *fireworks;
	std::vector<Particles::Fireworks*> vFire;

	for (int i = 0; i < 5; i++)
	{
		vFire.push_back(new Particles::Fireworks());
		vFire.back()->init(world, -999, -999);
	}

	int timer = 30;
	int currentFirework = 0;
	//fireworks->setColourRed();
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else
			{

			}
		}

		if (timer <= 0)
		{
			int x = rand() % 1280;
			int y = rand() % 720;
			vFire.at(currentFirework)->init(world, x, y);
			int rantemp = rand() % 3;
			if (rantemp == 0)
			{
				vFire.at(0)->setColourRed();
			}
			else if(rantemp == 1)
			{
				vFire.at(currentFirework)->setColourBlue();
			}
			else
			{
				vFire.at(currentFirework)->setColourGreen();
			}
			timer = 30;
			currentFirework++;
			if (currentFirework >= 5)
			{
				currentFirework = 0;
			}
		}
		else
		{
			timer--;
		}

		world->Step(0.1f, 1, 100);
		for (int i = 0; i < 5; i++)
		{
			vFire.at(i)->Render(renderer);
			vFire.at(i)->Update();
		}
		unsigned long milliseconds_since_epoch =
			std::chrono::system_clock::now().time_since_epoch() /
			std::chrono::milliseconds(1);
				srand(milliseconds_since_epoch);

		SDL_RendererFlip Flip = SDL_FLIP_NONE;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	return 0;
}