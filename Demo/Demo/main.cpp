#define SDL_MAIN_HANDLED

#include <iostream>
#include <FireWorks.h>
#include <SDL.h>
#include <Box2D\Box2D.h>
#include <time.h>
#include <random>
#include <vector>
#include "EventListener.h"
#include "BasicTypes.h"
#include "Renderer.h"
#include <stdio.h>

int main( int argc, char* args[])
{
	bool quit = false;
	SDL_Event e;

	Fireworks firworks;
	b2World* world;
	Renderer renderer;
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	world = new b2World(b2Vec2(0.0, 9.91));
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
			{
				printf("SDL could not initialise! SDL_ERROR: %s\n", SDL_GetError());
			}
			else
			{
				window = SDL_CreateWindow("Fireworks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

				screenSurface = SDL_GetWindowSurface(window);
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
				
				firworks.init(world);
				firworks.Render(renderer);
				world->Step(1.0 / 30.0, 8, 3);
				firworks.Update(60);
				SDL_UpdateWindowSurface(window);
			}
		}
	}
	return 0;
}
