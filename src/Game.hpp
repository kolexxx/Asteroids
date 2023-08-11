#pragma once

#include <SDL.h>

class Entity;
class Player;

constexpr float WINDOW_WIDTH = 720.f;
constexpr float WINDOW_HEIGHT = 720.f;

class Game
{
public:
	static void Start();
	static void Quit();
	inline static SDL_Window* Window() { return s_window; }

	static Player* s_player;
private:
	static bool s_isRunning;
	static SDL_Window* s_window;

	static void Loop();

	friend int main(int, char**);
};