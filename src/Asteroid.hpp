#pragma once

#include "Entity.hpp"
#include <string>
#include <vector>

constexpr uint32_t MAX_ASTEROIDS = 10;

class Asteroid : public Entity
{
public:
	static uint32_t NumOfAsteroids;
	static std::vector<std::string> BoomSounds;
	static std::vector<SDL_Texture*> Textures;
	
	static Asteroid& SpawnFromEdge();

	Asteroid(int level);
	~Asteroid();

protected:
	void Frame() override;

private:
	int m_level;
};