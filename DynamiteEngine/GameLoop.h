#pragma once

#include "Game.h"

class GameLoop
{
public:
	GameLoop();

	~GameLoop();

	int init();

private:
	Game* game = nullptr;
};