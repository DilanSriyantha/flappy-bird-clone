#pragma once

#include "ECS.h"
#include "Components.h"
#include "Game.h"
#include "AudioManager.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update();

	//void update() override
	//{
	//	if (Game::event.type == SDL_KEYDOWN)
	//	{
	//		switch (Game::event.key.keysym.sym)
	//		{
	//		case SDLK_w:
	//			transform->velocity.y = -1;
	//			sprite->playAnimation("Walk");
	//			break;

	//		case SDLK_a:
	//			transform->velocity.x = -1;
	//			sprite->playAnimation("Walk");
	//			sprite->sprite_flip = SDL_FLIP_HORIZONTAL;
	//			break;

	//		case SDLK_d:
	//			transform->velocity.x = 1;
	//			sprite->playAnimation("Walk");
	//			break;

	//		case SDLK_s:
	//			transform->velocity.y = 1;
	//			sprite->playAnimation("Walk");
	//			break;

	//		case SDLK_UP:
	//			if (Game::audio_manager->getVolumeMusic() < 128)
	//				Game::audio_manager->setVolumeMusic(Game::audio_manager->getVolumeMusic() + 1);

	//			std::cout << Game::audio_manager->getVolumeMusic() << std::endl;
	//			break;

	//		case SDLK_DOWN:
	//			if (Game::audio_manager->getVolumeMusic() > 0)
	//				Game::audio_manager->setVolumeMusic(Game::audio_manager->getVolumeMusic() - 1);

	//			std::cout << Game::audio_manager->getVolumeMusic() << std::endl;
	//			break;

	//		case SDLK_LEFT:
	//			//Game::audio_manager->setVolumeChannel(1, 0);

	//		default:
	//			break;
	//		}
	//	}

	//	if (Game::event.type == SDL_KEYUP)
	//	{
	//		switch (Game::event.key.keysym.sym)
	//		{
	//		case SDLK_w:
	//			transform->velocity.y = 0;
	//			sprite->playAnimation("Idle");
	//			break;

	//		case SDLK_a:
	//			transform->velocity.x = 0;
	//			sprite->playAnimation("Idle");
	//			sprite->sprite_flip = SDL_FLIP_NONE;
	//			break;

	//		case SDLK_d:
	//			transform->velocity.x = 0;
	//			sprite->playAnimation("Idle");
	//			break;

	//		case SDLK_s:
	//			transform->velocity.y = 0;
	//			sprite->playAnimation("Idle");
	//			break;

	//		case SDLK_ESCAPE:
	//			//Game::isRunning = false;
	//			Game::isPaused ? Game::isPaused = false : Game::isPaused = true;
	//			//Game::audio_manager->playSfx("sfx_swooshing", 0);
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}
};