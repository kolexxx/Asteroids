#include "Game.hpp"

#include "Entity.hpp"
#include "Player.hpp"
#include "Graphics.hpp"
#include "Time.hpp"
#include "Input.hpp"
#include "Asteroid.hpp"
#include "Saucer.hpp"
#include "Sound.hpp"

void Game::Start()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	s_window = SDL_CreateWindow("Asteroids", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

	Graphics::Init();
	Sound::Init();

	Asteroid::Textures =
	{
		Graphics::LoadTexture("res/asteroid1.bmp"),
		Graphics::LoadTexture("res/asteroid2.bmp"),
		Graphics::LoadTexture("res/asteroid3.bmp")
	};

	s_isRunning = true;
	Loop();
}

void Game::Loop()
{
	auto timeUntilAsteroidSpawn = TimeUntil();
	uint32_t lastTime = 0;
	uint32_t elapsedTime = 0;
	bool spawningAsteroids = false;
	srand(Time::Ticks());

	while (s_isRunning)
	{
		lastTime = Time::Ticks();

		Input::Build();
		Graphics::Clear();

		if (s_player == nullptr)
		{
			Graphics::DrawText("PRESS SPACE TO START", Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f, true);

			if (Input::Pressed(' '))
			{
				Entity::ClearList();
				s_player = new Player();
				s_asteroidsToSpawn = 4;
			}
		}
		else
		{
			if (!spawningAsteroids && s_numOfEnemies == 0)
			{
				spawningAsteroids = true;
				timeUntilAsteroidSpawn = 2.f;
			}
			else if (spawningAsteroids && timeUntilAsteroidSpawn)
			{
				spawningAsteroids = false;
				s_timeUntilSaucerSpawn = 12.f;
				SpawnEnemies();
			}

			if (!spawningAsteroids && s_timeUntilSaucerSpawn && s_saucer == nullptr)
			{
				s_saucer = new Saucer(rand() % 10 < 3);
			}

			Entity::UpdateList();
			Entity::CheckCollisions();

			for (auto* entity : Entity::All())
				entity->Tick();

			for (auto* entity : Entity::All())
				entity->Frame();
		}

		Graphics::Present();
		elapsedTime = Time::Ticks() - lastTime;

		if (TICK_TIME > elapsedTime)
		{
			SDL_Delay(TICK_TIME - elapsedTime);
		}

		Time::s_delta = (Time::Ticks() - lastTime) / 1000.f;
	}
}

void Game::SpawnEnemies()
{
	for (auto i = 0; i < s_asteroidsToSpawn; i++)
		new Asteroid(3);

	s_asteroidsToSpawn++;
}

void Game::Quit()
{
	SDL_DestroyWindow(s_window);
	SDL_DestroyRenderer(Graphics::s_renderer);
	SDL_Quit();
	s_isRunning = false;
}

uint32_t Game::s_asteroidsToSpawn = 4;
TimeUntil Game::s_timeUntilSaucerSpawn = {};
bool Game::s_isRunning = false;
SDL_Window* Game::s_window = nullptr;
uint32_t Game::s_numOfEnemies = 0;
Player* Game::s_player = nullptr;
Saucer* Game::s_saucer = nullptr;
