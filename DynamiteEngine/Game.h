#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include "Camera.h"

// it's a declaration
// this whole file is a kind of definition header
// it is called full declaration
// implementation file requires to be included the 
// original header file which contains the ColliderComponent 
// although
class ColliderComponent;
class AssetManager;
class AudioManager;
class Scene;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void addScene(std::string scene_id, Scene* scene);
	void setActiveScene(std::string scene_id);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static bool isPaused;
	static Camera camera;
	//static Manager* manager;
	static AssetManager* assets;
	static AudioManager* audio_manager;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupProjectiles,
		groupObjects,
		groupColliders,
		groupUIElements
	};

private:
	SDL_Window* window;
	std::map<std::string, Scene*> scenes;
	std::string active_scene_id;
};