#pragma once

#include <string>
#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"
#include "UILabel.h"

class ColliderComponent : public Component
{
public:
	int id = rand();
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int width, int height)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = height;
		collider.w = width;
	}

	ColliderComponent(std::string t, int xpos, int ypos, int width, int height, bool show_gizmo)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = height;
		collider.w = width;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("assets/tile_collider.png");
		srcRect = { 0, 0, 32, 32 };
		destRect = { collider.x, collider.y, collider.w, collider.h };

		//Game::colliders.push_back(this);
	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		if (show_gizmo) 
		{
			TextureManager::Draw(tex, srcRect, destRect, SDL_FLIP_NONE);
		}
	}

private:
	bool show_gizmo = false;
};