#pragma once

#include "DynamiteEngine.h"

class Bird
{
public:
	bool isFalling = false;
	bool isHit = false;

	Bird(Manager& manager);

	~Bird();

	void init();

	void update(float& elapsed_time);

	Vector2D position();

	float w();

	float h();

	void wing();

	void hit();
	
	void fall();

	void reset();

	bool isColliding(SDL_Rect& obs_collider);

private:
	float velocity = 0.0f;
	float acceleration = 0.0f;
	const float gravity = 100.0f;
	Entity* bird;
};