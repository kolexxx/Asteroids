#pragma once

#include "Entity.hpp"
#include <string>
#include <vector>

constexpr uint32_t MAX_ASTEROIDS = 10;

class Asteroid : public Entity
{
public:
	static std::vector<SDL_Texture*> Textures;

	Asteroid(int level);
	~Asteroid();

	void Frame() override;
	void Touch( Entity& other ) override;
	uint32_t CalculateReward() override;

private:
	static std::vector<std::string> s_boomSounds;
	int m_level;
};