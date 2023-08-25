#pragma once

#include "Entity.hpp"
#include "Time.hpp"

class Saucer : public Entity
{
public:
	Saucer( bool small  );
	~Saucer();

	void Tick() override;
	void Frame() override;
	void Touch( Entity& other ) override;
	uint32_t CalculateReward() override;

private:
	Vector2 m_direction;
	bool m_small;
	uint32_t m_sirenSound;
	TimeUntil m_timeUntilCanFire;
};