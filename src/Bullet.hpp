#pragma once

#include "Entity.hpp"
#include "Time.hpp"

class Bullet : public Entity
{
public:
	Bullet( Entity* owner, Vector2 position, float angle );

	void Tick() override;
	void Frame() override;
	void Touch( Entity& other ) override;

private:
	Entity* m_owner;
	float m_speed;
	TimeUntil m_timeUntilDelete;
};