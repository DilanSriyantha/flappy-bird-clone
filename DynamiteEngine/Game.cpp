#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "AudioManager.h"
#include "Scene.h"
#include <sstream>

extern void sceneInit();
extern void sceneUpdate();

Map* map;
Manager manager;

//Manager* Game::manager = new Manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Camera Game::camera = { 0, 0, 800, 640 };

AssetManager* Game::assets = new AssetManager(&manager);
AudioManager* Game::audio_manager = audio_manager = new AudioManager(44100, MIX_DEFAULT_FORMAT, 2, 1024); // initialized with recommended values;

bool Game::isRunning = false;
bool Game::isPaused = false;

//auto& player(manager.addEntity());
//auto& label(manager.addEntity());
//auto& label_cam_position(manager.addEntity());
//auto& canvas(manager.addEntity());
//auto& label_menu_item_1(manager.addEntity());
//auto& label_menu_item_2(manager.addEntity());
//auto& label_menu_item_3(manager.addEntity());

Game::Game()
{

}

Game::~Game()
{

}

void Game::addScene(std::string scene_id, Scene* scene)
{
	scenes.emplace(scene_id, std::move(scene));
}

void Game::setActiveScene(std::string scene_id)
{
	active_scene_id = scene_id;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// handle flags
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		// initialize window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// intialize renderer
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		// intialize Game::renderer
		Game::Game::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer)
		{
			// set draw color
			SDL_SetRenderDrawColor(Game::renderer, 0xff, 0xff, 0xff, 0xff);

			std::cout << "renderer created!" << std::endl;
		}

		// set running flag to true;
		isRunning = true;
	}
	
	// initialize sdl_ttf
	if (TTF_Init() < 0)
	{
		std::cout << "Could not initialize SDL2_TTF" << std::endl << "TTF_Error: " << TTF_GetError() << std::endl;
	}

	// initialize audio manager
	if (audio_manager->init() < 0)
	{
		std::cout << "Could not initialize AudioManager: " << audio_manager->getError() << std::endl;
	}

	sceneInit();

	//audio_manager->addMusic("bgm", "assets/town_theme.wav");
	//audio_manager->addSfx("sfx_swooshing", "assets/everything/sfx_swooshing.wav");
	//audio_manager->playMusic("bgm", -1);
	//
	//assets->addTexture("terrain", "assets/tile_set_6.png");
	//assets->addTexture("player", "assets/player_anims.png");
	//assets->addTexture("projectile", "assets/projectile.png");
	//assets->addFont("arial", "assets/arial.ttf", 16);
	//
	//map = new Map("terrain", 3, 32);

	// ecs implementation

	//map->Map::LoadMap("assets/map_new_1.map", 25, 20);
	//
	//player.addComponent<TransformComponent>(2);
	//player.addComponent<SpriteComponent>("player", true);
	//player.addComponent<KeyboardController>();
	//player.addComponent<ColliderComponent>("player", 0, 0, 64);
	//player.addGroup(Game::groupPlayers);
	//
	//SDL_Color color = { 0xff, 0xff, 0xff, 0xff };
	//label.addComponent<UILabel>("", "arial", color, 10, 10);
	//label.addGroup(Game::groupUIElements);
	//
	//label_cam_position.addComponent<UILabel>("", "arial", color, 10, 29);
	//label_cam_position.addGroup(Game::groupUIElements);
	//
	//label_menu_item_1.addComponent<UILabel>("New Game", "arial", color, 400, 280);
	//label_menu_item_2.addComponent<UILabel>("Options", "arial", color, 400, 300);
	//label_menu_item_2.addComponent<UILabel>("Quit", "arial", color, 400, 320);
	//
	//canvas.addComponent<Canvas>(0, 0, 800, 640, false);
	//canvas.getComponent<Canvas>().addChild(&label_menu_item_1);
	//canvas.getComponent<Canvas>().addChild(&label_menu_item_2);
	//canvas.getComponent<Canvas>().addChild(&label_menu_item_3);
	//canvas.addGroup(Game::groupUIElements);
	//
	//assets->createProjectile(Vector2D(0, 0), Vector2D(2, 0), 200, 2, "projectile");
}

auto& tiles = manager.getGroup(Game::groupMap);
auto& players = manager.getGroup(Game::groupPlayers);
auto& projectiles = manager.getGroup(Game::groupProjectiles);
auto& colliders = manager.getGroup(Game::groupColliders);
auto& ui_elements = manager.getGroup(Game::groupUIElements);
auto& objects = manager.getGroup(Game::groupObjects);

void Game::handleEvents()
{
	// intialize an event
	SDL_PollEvent(&event);

	// handle events
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	//SDL_Rect player_collider = player.getComponent<ColliderComponent>().collider;
	//Vector2D player_position = player.getComponent<TransformComponent>().position;
	//
	//std::stringstream ss;
	//ss << "Player position: " << player_position;
	//label.getComponent<UILabel>().setText(ss.str(), "arial");
	//
	//std::stringstream ss_cam_position;
	//ss_cam_position<< "Camera#1 Position: (" << camera.x << "," << camera.y << ")";
	//label_cam_position.getComponent<UILabel>().setText(ss_cam_position.str(), "arial");

	sceneUpdate();

	manager.refresh();
	manager.update();
	
	//for (auto& c : colliders)
	//{
	//	SDL_Rect c_col = c->getComponent<ColliderComponent>().collider;
	//	if (Collision::AABB(c_col, player_collider))
	//	{
	//		player.getComponent<TransformComponent>().position = player_position;
	//
	//		std::cout << "collission detected (player | " << c->getComponent<ColliderComponent>().id << ")" <<  std::endl;
	//	}
	//}
	//
	//for (auto& p : projectiles)
	//{
	//	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
	//	{
	//		std::cout << "Hit player!" << std::endl;
	//		p->destroy();
	//	}
	//}
	
	//camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	//camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	if (camera.x < 0)
		camera.x = 0;

	if (camera.y < 0)
		camera.y = 0;

	if (camera.x > camera.w)
		camera.x = camera.w;

	if (camera.y > camera.h)
		camera.y = camera.h;

	//if (isPaused)
	//	canvas.getComponent<Canvas>().setVisibile(true);
	//else
	//	canvas.getComponent<Canvas>().setVisibile(false);
}

void Game::render()
{
	// clear screen
	SDL_RenderClear(Game::renderer);

	// this is where we would add stuff to render //

	manager.draw();

	for (auto& t : tiles)
	{
		t->draw();
	}
	
	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& o : objects)
	{
		o->draw();
	}

	for (auto& uie : ui_elements)
	{
		uie->draw();
	}

	//SDL_RenderDrawRect(Game::renderer, Game::camera.getRect());
	SDL_RenderSetViewport(Game::renderer, Game::camera.getRect());
	////////////////////////////////////////////////

	// update the screen
	SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
	// destroy window
	SDL_DestroyWindow(window);
	
	// destroy renderer
	SDL_DestroyRenderer(Game::renderer);

	// perform quit 
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}