#pragma once

#include "Components.h"
#include "Vector2D.h"
#include <oaidl.h>

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		//position.Zero();

		/*
		* in order to map scrolling camera angle implementation
		* we have to keep the player static in the middle of the
		* screen.
		*/
		position.x = 400;
		position.y = 320;

		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void normalize(float x, float y)
	{
		float magnitude = std::sqrt(x * x + y * y);

		// avoid divition by zero
		if (magnitude > 0.0f)
		{
			x /= magnitude;
			y /= magnitude;
		}
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		normalize(velocity.x, velocity.y);

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};