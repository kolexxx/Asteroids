#pragma once

#include "Entity.hpp"
#include "Sound.hpp"
#include "Time.hpp"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Tick() override;
	void Frame() override;
	void Touch( Entity& other ) override;
	void TakeHit() override;
	void Reset();
	void AddScore( uint32_t score );
	bool IsRespawning();
	uint32_t GetScore();

private:
	uint32_t m_lives;
	uint32_t m_score;
	TimeUntil m_timeUntilCanFire;
	TimeUntil m_respawnTime;
	int32_t m_thrustSoundChannel;
};