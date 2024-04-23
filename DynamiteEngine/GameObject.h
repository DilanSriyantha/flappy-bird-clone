#pragma once

#include "ECS.h"
#include "Components.h"

class GameObject : public Component
{
public:
	GameObject();
	~GameObject();

	void update();
	void render();

private:
	int xpos;
	int ypos;

	SDL_Texture* object_texture;
	SDL_Rect srcRect, destRect;
};

