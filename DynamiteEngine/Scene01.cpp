#include "Scene01.h"
#include "Collision.h"
#include <map>
#include <algorithm>
#include <sstream>
#include "Bird.h"

Bird bird(manager);


auto& bg_tile(manager.addEntity());
auto& bg_base(manager.addEntity());
auto& canvas(manager.addEntity());
auto& game_over_banner(manager.addEntity());
auto& canvas_message_container(manager.addEntity());
auto& message_banner(manager.addEntity());
auto& press_space_banner(manager.addEntity());
auto& score_label(manager.addEntity());
auto& final_score_label(manager.addEntity());

std::vector<Entity*> base_tiles;
std::vector<Entity*> obstacle_sections;

int obs_x_pos = 800.0f;
int current_x_pos = 0.0f;

bool flag_game_started = false;
bool flag_game_over = false;

float elapsed_time = 0.0f;

float score = 0.0f;

void sceneInit()
{

	Game::assets->addTexture("bg-tile", "assets/fb/bg-day.png");
	Game::assets->addTexture("bg-base", "assets/fb/base.png");
	Game::assets->addTexture("game-over-banner", "assets/fb/gameover.png");
	Game::assets->addTexture("press-space-banner", "assets/fb/press_space.png");
	Game::assets->addTexture("message-banner", "assets/fb/message.png");
	Game::assets->addTexture("pipe-up", "assets/fb/pipe_green_up.png");
	Game::assets->addTexture("pipe-down", "assets/fb/pipe_green_down.png");
	Game::assets->addTexture("0", "assets/fb/0.png");
	Game::assets->addTexture("1", "assets/fb/1.png");
	Game::assets->addTexture("2", "assets/fb/2.png");
	Game::assets->addTexture("3", "assets/fb/3.png");
	Game::assets->addTexture("4", "assets/fb/4.png");
	Game::assets->addTexture("5", "assets/fb/5.png");
	Game::assets->addTexture("6", "assets/fb/6.png");
	Game::assets->addTexture("7", "assets/fb/7.png");
	Game::assets->addTexture("8", "assets/fb/8.png");
	Game::assets->addTexture("9", "assets/fb/9.png");

	Game::assets->addFont("mct-16", "assets/fb/MinecraftTen.ttf", 16);
	Game::assets->addFont("mct-24", "assets/fb/MinecraftTen.ttf", 24);
	Game::assets->addFont("mct-32", "assets/fb/MinecraftTen.ttf", 32);
	Game::assets->addFont("mct-64", "assets/fb/MinecraftTen.ttf", 64);

	Game::audio_manager->addSfx("sfx-wing", "assets/fb/sfx_wing.wav");
	Game::audio_manager->addSfx("sfx-hit", "assets/fb/sfx_hit.wav");
	Game::audio_manager->addSfx("sfx-die", "assets/fb/sfx_die.wav");
	Game::audio_manager->addMusic("bgm", "assets/fb/8_bit_adventure.wav");

	bird.init();

	bg_tile.addComponent<TransformComponent>(0.0f, 0.0f, 640, 800, 1);
	bg_tile.addComponent<SpriteComponent>("bg-tile");
	bg_tile.addGroup(Game::groupMap);

	base_tiles.push_back(std::move(createBaseTile(0.0f)));
	base_tiles.push_back(std::move(createBaseTile(800.0f)));
	base_tiles.push_back(std::move(createBaseTile(1600.0f)));

	canvas.addComponent<Canvas>(0, 0, 800, 640, false);
	canvas.addGroup(Game::groupUIElements);

	canvas_message_container.addComponent<Canvas>(0, 0, 800, 640, !flag_game_started);
	canvas_message_container.addGroup(Game::groupUIElements);

	game_over_banner.addComponent<TransformComponent>(200.0f, 280.0f, 42, 192, 2);
	game_over_banner.addComponent<SpriteComponent>("game-over-banner");

	press_space_banner.addComponent<TransformComponent>(284.0f, 352.0f, 42, 96, 2);
	press_space_banner.addComponent<SpriteComponent>("press-space-banner");

	message_banner.addComponent<TransformComponent>(308.0f, 206.0f, 268, 184, 1);
	message_banner.addComponent<SpriteComponent>("message-banner");

	SDL_Color color = { 0xff, 0xff, 0xff, 0xff };
	score_label.addComponent<UILabel>("0", "mct-32", color, 10, 10);
	score_label.addGroup(Game::groupUIElements);

	final_score_label.addComponent<UILabel>("0", "mct-64", color, 350, 186);
	
	canvas.getComponent<Canvas>().addChild(&game_over_banner);
	canvas.getComponent<Canvas>().addChild(&press_space_banner);
	canvas.getComponent<Canvas>().addChild(&final_score_label);
	canvas_message_container.getComponent<Canvas>().addChild(&message_banner);

	Game::audio_manager->playMusic("bgm", -1);
}

void sceneUpdate()
{
	if (Game::isPaused)
		return;

	bird.update(elapsed_time);


	if (bird.isFalling)
	{
		std::cout << "falling" << std::endl;
		bird.fall();
		gameOver();
	}

	//std::cout << bird_acceleration << std::endl;

	for (auto t : base_tiles)
	{
		if (t->getComponent<TransformComponent>().position.x <= -900.0f)
		{
			base_tiles.erase(base_tiles.begin());
			base_tiles.erase(std::remove(
				base_tiles.begin(),
				base_tiles.end(),
				t),
				base_tiles.end());
			base_tiles.push_back(createBaseTile(800.0f));

			std::cout << "new base tile drawn. new base tile vec size: " << base_tiles.size() << std::endl;
		}

		t->getComponent<TransformComponent>().position.x -= 1.0f;
	}

	if (flag_game_started)
	{
		canvas_message_container.getComponent<Canvas>().setVisibile(false);

		if (obstacle_sections.size() == 0)
		{
			createObstacleSection(852, 10);
			std::cout << "Initial obs vec size: " << obstacle_sections.size() << std::endl;
			std::cout << "Initial base tiles vec size: " << base_tiles.size() << std::endl;
		}
	}


	if (obstacle_sections.size() > 0)
	{
		for (auto& col : obstacle_sections)
		{
			auto& obs_collider_rect = col->getComponent<ColliderComponent>().collider;

			if (bird.isColliding(obs_collider_rect))
			{
				bird.hit();
				gameOver();
			}

			// calculating points collected
			if (bird.w() + bird.position().x == obs_collider_rect.x + obs_collider_rect.w + 52 && bird.position().x + bird.w() > obs_collider_rect.x + obs_collider_rect.w)
			{
				score += .5f;

				score_label.getComponent<UILabel>().setText(std::to_string((int)score), "mct-32");

				std::cout << "score : " << score << std::endl;
			}
		}

		for (auto& obs_sec : obstacle_sections)
		{
			obs_sec->getComponent<TransformComponent>().position.x -= 1.0f;

			if (obs_sec->getComponent<TransformComponent>().position.x < -104.0f)
			{
				obstacle_sections.erase(std::remove(
					obstacle_sections.begin(),
					obstacle_sections.end(),
					obs_sec),
					obstacle_sections.end());

				std::cout << "obs section removed, new size = " << obstacle_sections.size() << std::endl;
			}

			if(obstacle_sections.size() < 20)
				createObstacleSection(obs_x_pos, 1);
		}
	}

	obs_x_pos -= 1.0f;
}

void KeyboardController::update()
{
	//if (Game::event.type == SDL_KEYDOWN)
	//{
	//	switch (Game::event.key.keysym.sym)
	//	{
	//	case SDLK_SPACE:
	//		
	//	case SDLK_UP:
	//		std::cout << "UP" << std::endl;
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//else
	//{
	//	if (flag_game_started)
	//	{
	//		elapsed_time += 0.0001f;
	//	}
	//}

	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (flag_game_started) {
				bird.wing();
			}
			else if (!flag_game_started && !flag_game_over)
			{
				flag_game_started = true;
			}
			else if (flag_game_over && !flag_game_started)
			{
				resetGame();
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (flag_game_started)
		{
			elapsed_time += 0.0001f;
			//elapsed_time += 1.0f / 60.0f;
		}
	}
}

Entity* createBaseTile(int x_pos)
{
	auto& base_tile(manager.addEntity());
	base_tile.addComponent<TransformComponent>((float)x_pos, 540.0f, 100, 800, 1);
	base_tile.addComponent<SpriteComponent>("bg-base");
	base_tile.addGroup(Game::groupMap);

	return &base_tile;
}

void createObstacleSection(int x_pos, int section_density)
{
	for (int i = 0; i < section_density; i++)
	{
		int h1 = 10 + (rand() % 202); // offset + (rand() % range) 10 - 202 in this case
		int h2 = 240 - h1;
		int y1 = 540 - h1;

		auto& obs_up(manager.addEntity());
		obs_up.addComponent<TransformComponent>((float)x_pos, (float)y1, h1, 52, 1);
		obs_up.addComponent<SpriteComponent>("pipe-up");
		obs_up.addComponent<ColliderComponent>("obstacle", x_pos + (52 * i), y1, 52, h1);
		obs_up.addGroup(Game::groupColliders);

		auto& obs_down(manager.addEntity());
		obs_down.addComponent<TransformComponent>((float)x_pos, 0.0f, h2, 52, 1);
		obs_down.addComponent<SpriteComponent>("pipe-up");
		obs_down.getComponent<SpriteComponent>().sprite_flip = SDL_FLIP_VERTICAL;
		obs_down.addComponent<ColliderComponent>("obstacle", x_pos + (52 * i), 0, 52, h2);
		obs_down.addGroup(Game::groupColliders);

		obstacle_sections.push_back(&obs_up);
		obstacle_sections.push_back(&obs_down);

		x_pos += (52 * 2);
	}

	obs_x_pos = x_pos;

	std::cout << "new obs x position : " << obs_x_pos << std::endl;
}

void gameOver()
{
	std::cout << "Game over" << std::endl;

	flag_game_started = false;
	flag_game_over = true;
	Game::isPaused = true;
	final_score_label.getComponent<UILabel>().setText(std::to_string((int)score), "mct-64");
	canvas.getComponent<Canvas>().setVisibile(true);
}

void resetGame()
{
	obs_x_pos = 800.0f;
	current_x_pos = 0.0f;

	flag_game_started = false;
	flag_game_over = false;

	elapsed_time = 0.0f;

	score = 0;

	bird.reset();

	canvas.getComponent<Canvas>().setVisibile(false);
	canvas_message_container.getComponent<Canvas>().setVisibile(true);

	for (auto& obs : obstacle_sections)
	{
		obs->destroy();
	}
	obstacle_sections.clear();

	Game::isPaused = false;

	std::cout << "Game reset" << std::endl;
}