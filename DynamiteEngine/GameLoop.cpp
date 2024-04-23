#include "GameLoop.h"
#include <thread>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	642

GameLoop::GameLoop()
{}

GameLoop::~GameLoop()
{
	game->clean();
}

int GameLoop::init()
{
	// cap the framerate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("DynamiteEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running())
	{
		// get frame start milliseconds
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		// get framtime
		frameTime = SDL_GetTicks() - frameStart;

		// delay the frame and cap fps
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return 0;
}