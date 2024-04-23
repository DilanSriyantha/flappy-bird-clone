#pragma once

#include <string>

class Map
{
public:
	Map(std::string tid, int mscale, int tsize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void addTile(int srcX, int srcY, int xpos, int ypos);

private:
	std::string texture_id;
	int map_scale;
	int tile_size;
	int scaled_size;
};

