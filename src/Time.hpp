#pragma once

#include "Game.hpp"

class Time
{
public:
	inline static float Delta() { return s_delta; }
	inline static uint32_t Ticks() { return SDL_GetTicks(); }

	friend class Game;
private:
	static float s_delta;
};

class TimeUntil
{
public:
	TimeUntil( float time = 0.f );

	void operator=( float time );
	void operator+=( float time );
	operator bool() const;
private:
	uint32_t m_tick;
};