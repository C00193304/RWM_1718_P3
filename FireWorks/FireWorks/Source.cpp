#define SDL_MAIN_HANDLED

#include <iostream>
#include "SDL.h"
#include<Box2D\Box2D.h>
#include <time.h>
#include "FireWorks.h"
#include <random>
#include <vector>
#include "EventListener.h"
#include "BasicTypes.h"
#include <stdio.h>

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
	fireworks = new Particles::Fireworks();
	fireworks->init(world, 500, 500);
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
				world->Step(0.1f, 1, 100);
				fireworks->Render(renderer);
				fireworks->Update();

				SDL_RendererFlip Flip = SDL_FLIP_NONE;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderPresent(renderer);
				SDL_RenderClear(renderer);
			}
		}
	}
	return 0;
}