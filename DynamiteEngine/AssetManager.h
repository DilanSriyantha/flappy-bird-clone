#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager* _manager);
	~AssetManager();

	// game objects
	void createProjectile(Vector2D _position, Vector2D _velocity, int _range, int _speed, std::string _tid);

	// texture management
	void addTexture(std::string id, const char* path);
	SDL_Texture* getTexture(std::string id);

	// font management
	void addFont(std::string id, const char* f_path, int f_size);
	TTF_Font* getFont(std::string id);

private:
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
	Manager* manager;
};