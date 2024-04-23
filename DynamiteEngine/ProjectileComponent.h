#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int _range, int _speed, Vector2D _velocity)
		: range(_range), speed(_speed), velocity(_velocity)
	{}

	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "Out of range" << std::endl;
			entity->destroy();
		}
		else if
			(
				transform->position.x > Game::camera.x + Game::camera.w ||
				transform->position.x < Game::camera.x ||
				transform->position.y > Game::camera.y + Game::camera.h ||
				transform->position.y < Game::camera.y
				)
		{
			std::cout << "Out of bounds" << std::endl;
			entity->destroy();
		}
	}

private:
	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};