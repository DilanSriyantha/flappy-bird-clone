#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* _manager)
	: manager(_manager)
{}

AssetManager::~AssetManager()
{
	// cleanup textures
	AssetManager::textures.clear();
	AssetManager::fonts.clear();
	AssetManager::manager = nullptr;
}

void AssetManager::createProjectile(Vector2D _position, Vector2D _velocity, int _range, int _speed, std::string _tid)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(_position.x, _position.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(_tid);
	projectile.addComponent <ProjectileComponent>(_range, _speed, _velocity);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::addTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
	return textures[id];
}

void AssetManager::addFont(std::string id, const char* f_path, int f_size)
{
	TTF_Font* font = TTF_OpenFont(f_path, f_size);
	fonts.emplace(id, font);
}

TTF_Font* AssetManager::getFont(std::string id)
{
	return fonts[id];
}