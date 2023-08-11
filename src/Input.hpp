#pragma once

#include "Game.hpp"

#include <array>

class Input
{
public:
	static bool Pressed(char key);
	static bool Down(char key);
	static bool Released(char key);

	friend class Game;
private:
	static void Build();

	static std::array<bool, 91> s_pressed;
	static std::array<bool, 91> s_down;
	static std::array<bool, 91> s_released;
};