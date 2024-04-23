#pragma once

#include <string>
#include "SDL_ttf.h"
#include "SDL.h"
#include "ECS.h"
#include "AssetManager.h"
#include "Game.h"

class UILabel : public Component
{
public:
	UILabel(std::string text, std::string f_name, SDL_Color f_color, int xpos, int ypos)
		: label_text(text), font_name(f_name), font_color(f_color)
	{
		dest_rect.x = xpos;
		dest_rect.y = ypos;

		setText(text, f_name);
	}

	~UILabel()
	{
		SDL_DestroyTexture(font_texture);
	}

	void setText(std::string text, std::string f_id)
	{
		// if texture is not null,
		// cleanup the texture before creating new one
		if (font_texture != nullptr)
		{
			SDL_DestroyTexture(font_texture);
		}

		// create a temporary surface
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assets->getFont(f_id), text.c_str(), font_color);

		// create texture from the surface
		font_texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

		// clear the surface
		SDL_FreeSurface(surface);

		// use SDL_QueryTexture method since we don't know 
		// the width of the texture certainly
		SDL_QueryTexture(font_texture, nullptr, nullptr, &dest_rect.w, &dest_rect.h);
	}

	void updatePosition(int x, int y)
	{
		dest_rect.x = x;
		dest_rect.y = y;

		setText(label_text, font_name);
	}

	void draw() override
	{
		// draw the texture
		SDL_RenderCopy(Game::renderer, font_texture, nullptr, &dest_rect);
	}
private:
	std::string label_text;
	std::string font_name;
	SDL_Color font_color;
	SDL_Rect dest_rect;
	SDL_Texture* font_texture;
};