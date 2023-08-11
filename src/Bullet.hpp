#pragma once

#include "Entity.hpp"
#include "Time.hpp"

class Bullet : public Entity
{
public:
	Bullet( Vector2 position, float angle );

	void Tick() override;
	void Frame() override;
	void Touch( Entity& other ) override;
private:
	float m_speed;
	TimeUntil m_timeUntilDelete;
};