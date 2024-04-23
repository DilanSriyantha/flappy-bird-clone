#pragma once

#include "Components.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Animation.h"
#include <map>
#include "AssetManager.h"
#include "Game.h"

class SpriteComponent : public Component
{
public:
	// helpful to handle multiple animations
	int animIndex = 0;

	// to store animations
	std::map<const char*, Animation> animations;

	// helpful to flip the 2d characters horizontally and vertically
	SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id)
	{
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 180);
		Animation walk = Animation(2, 10, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		playAnimation("Idle");
		setTex(id);
	}

	~SpriteComponent()
	{

	}

	void setTex(std::string id)
	{
		// load texture
		texture = Game::assets->getTexture(id);
	}

	void init() override
	{
		// initialize the position using the entity
		transform = &entity->getComponent<TransformComponent>();

		// initialize source rectangle attributes
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		// intialize destination rectangle attributes
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void update() override
	{
		// animation
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		// update position attributes of destination rectangle
		/*destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;*/

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		// draw textures
		TextureManager::Draw(texture, srcRect, destRect, sprite_flip);
	}

	void playAnimation(const char* anim_name)
	{
		frames = animations[anim_name].frames;
		animIndex = animations[anim_name].index;
		speed = animations[anim_name].speed;
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100; // delay between frames in milliseconds
};