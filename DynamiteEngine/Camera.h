#pragma once

#include "SDL.h"

class Camera
{
public:
	int x;
	int y;
	int w;
	int h;

	Camera(int x_pos, int y_pos, int width, int height)
	{
		x = x_pos;
		y = y_pos;

		w = width;
		h = height;

		cam_rect.x = x;
		cam_rect.y = y;
		cam_rect.w = w;
		cam_rect.h = h;
	}

	~Camera()
	{}

	SDL_Rect* getRect()
	{
		return &cam_rect;
	}

private:
	SDL_Rect cam_rect;
};