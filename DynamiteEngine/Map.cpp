#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"

// extern keyword tells the compiler that this
// instance of the manager class is a different 
// variable instead of the one which is in game.cpp
extern Manager manager;

Map::Map(std::string tid, int mScale, int tSize)
	: texture_id(tid), map_scale(mScale), tile_size(tSize)
{
	scaled_size = mScale * tSize;
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream map_file;

	map_file.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			map_file.get(c);
			srcY = atoi(&c) * tile_size;

			map_file.get(c);
			srcX = atoi(&c) * tile_size;

			addTile(srcX, srcY, x * (tile_size * map_scale), y * (tile_size * map_scale));
			map_file.ignore();
		}
	}

	map_file.ignore();

	// load collision map
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			map_file.get(c);
			if (c == '1')
			{
				auto& tile_collider(manager.addEntity());
				tile_collider.addComponent<ColliderComponent>("terrain", x * scaled_size, y * scaled_size, scaled_size);
				tile_collider.addGroup(Game::groupColliders);
			}
			// if c = 0 we should ignore the character
			map_file.ignore();
		}
	}

	map_file.close();
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tile_size, map_scale, texture_id);
	tile.addGroup(Game::groupMap);
}