#define SDL_MAIN_HANDLED

#include <iostream>
#include "FireWorks.h"
#include <SDL.h>
#include <Box2D\Box2D.h>
#include <time.h>
#include <random>
#include <vector>
#include "EventListener.h"
#include "BasicTypes.h"
#include <stdio.h>

int main( int argc, char* args[])
{
	bool quit = false;
	SDL_Event e;
	
	Particles::Fireworks firworks;
	b2World* world;
	SDL_Renderer* renderer;
	SDL_Window* window = SDL_CreateWindow("fireworks!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Surface* screenSurface = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	world = new b2World(b2Vec2(0.0, 9.91));
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
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderClear(renderer);
				SDL_RendererFlip Flip = SDL_FLIP_NONE;
				SDL_RenderPresent(renderer);
				firworks.init(world);
				firworks.Render(*renderer);
				world->Step(1.0 / 30.0, 8, 3);
				firworks.Update(60, 255, 255, 255);
			}
		}
	}
	return 0;
}
