#pragma once

#include <SDL.h>

class Entity;
class Player;
class Saucer;
class TimeUntil;

constexpr float WINDOW_WIDTH = 800.f;
constexpr float WINDOW_HEIGHT = 800.f;
constexpr uint32_t TICK_TIME = 1000 / 60;

class Game
{
public:
	static void Start();
	static void Quit();
	inline static SDL_Window* Window() { return s_window; }

	static Player* s_player;
	static Saucer* s_saucer;
	static uint32_t s_numOfEnemies;
	static TimeUntil s_timeUntilSaucerSpawn;
private:
	static uint32_t s_asteroidsToSpawn;
	static bool s_isRunning;
	static SDL_Window* s_window;

	static void Loop();
	static void SpawnEnemies();
};