#pragma once

#include "Components.h"
#include <vector>

class Canvas : public Component
{
public:
	Canvas(int x_pos, int y_pos, int c_width, int c_height, bool c_visible)
		: x(x_pos), y(y_pos), width(c_width), height(c_height), visible(c_visible)
	{
		background_rect.x = x_pos;
		background_rect.y = y_pos;
		background_rect.w = c_width;
		background_rect.h = c_height;

		background_color = { 0x00, 0x00, 0x00, 0x80 };
	}

	~Canvas()
	{}

	void addChild(Entity* entity)
	{
		children.emplace_back(std::move(entity));
	}

	void setVisibile(bool flag)
	{
		visible = flag;
	}

	void draw() override
	{
		if (visible) {
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(Game::renderer, background_color.r, background_color.g, background_color.b, background_color.a);
			SDL_RenderFillRect(Game::renderer, &background_rect);
			SDL_SetRenderDrawColor(Game::renderer, 0xff, 0xff, 0xff, 0xff);
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_NONE);

			for (auto& c : children)
			{
				c->draw();
			}
		}
	}

	void update() override
	{
		for (auto& c : children)
		{
			c->update();
		}
	}

private:
	int width;
	int height;
	int x;
	int y;
	bool visible;
	SDL_Color background_color;
	SDL_Rect background_rect;
	std::vector<Entity*> children;
};