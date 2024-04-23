#include "Bird.h"

Bird::Bird(Manager& manager)
{
	auto& player(manager.addEntity());
	bird = &player;
}

Bird::~Bird()
{

}

void Bird::init()
{
	Game::assets->addTexture("player", "assets/fb/flappy_bird_sheet.png");

	Game::audio_manager->addSfx("sfx-wing", "assets/fb/sfx_wing.wav");
	Game::audio_manager->addSfx("sfx-git", "assets/fb/sfx_hit.wav");
	Game::audio_manager->addSfx("sfx-die", "assets/fb/sfx_die.wav");

	bird->addComponent<TransformComponent>(100.0f, 270.0f, 32, 32, 1);
	bird->addComponent<SpriteComponent>("player", true);
	bird->addComponent<ColliderComponent>("player", 0, 0, 32);
	bird->addComponent<KeyboardController>();
	bird->addGroup(Game::groupObjects);
}

void Bird::update(float& elapsed_time)
{
	acceleration += gravity * elapsed_time;

	if (acceleration >= gravity)
		acceleration = gravity;

	velocity += acceleration * elapsed_time;

	bird->getComponent<TransformComponent>().position.y += velocity * elapsed_time;

	//std::cout << "acceleration: " << acceleration << std::endl;
	//std::cout << "velocity: " << velocity << std::endl;
	//std::cout << "positionY: " << bird->getComponent<TransformComponent>().position.y << std::endl;
	//std::cout << "elapsed time: " << elapsed_time << std::endl;

	if (bird->getComponent<TransformComponent>().position.y > 600.0f)
	{
		isFalling = true;
	}
	else
	{
		isFalling = false;
	}
	
	if (bird->getComponent<TransformComponent>().position.y <= 0.0f)
	{
		bird->getComponent<TransformComponent>().position.y = 0.0f;
	}
}

Vector2D Bird::position()
{
	return bird->getComponent<TransformComponent>().position;
}

float Bird::w()
{
	return bird->getComponent<TransformComponent>().width;
}

float Bird::h()
{
	return bird->getComponent<TransformComponent>().height;
}

void Bird::wing()
{
	acceleration = 0.0f;
	velocity = -gravity / 2.0f;

	Game::audio_manager->playSfx("sfx-wing", 0);
}

void Bird::hit()
{
	Game::audio_manager->playSfx("sfx-hit", 0);
}

void Bird::fall()
{
	Game::audio_manager->playSfx("sfx-die", 0);
}

bool Bird::isColliding(SDL_Rect& obs_collider)
{
	if(Collision::AABB(obs_collider, bird->getComponent<ColliderComponent>().collider))
	{
		return true;
	}
	return false;
}

void Bird::reset()
{
	float velocity = 0.0f;
	float acceleration = 0.0f;

	bird->getComponent<TransformComponent>().position.y = 270.0f;
}