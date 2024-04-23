#pragma once

#include "DynamiteEngine.h"
#include <string>

extern Manager manager;

void sceneInit();

void sceneUpdate();

Entity* createBaseTile(int x_pos);

void createObstacleSection(int x_pos, int section_density);

void gameOver();

void resetGame();