#pragma once

#include <vector>
#include "ECS.h"

class Scene
{
public:
	std::vector<Entity*> scene_entities;

	Scene() {};

	~Scene() {};

	virtual void init();
	virtual void render();
	virtual void update();
};