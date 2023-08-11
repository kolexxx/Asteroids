#pragma once

#include "Game.hpp"
#include "Graphics.hpp"
#include "Math/Vector2.hpp"

#include <vector>

class Entity
{
public:
	Entity(Vector2 position, Vector2 BBox, float angle = 0);

	static inline const std::vector<Entity*>& All() { return s_all; }

	virtual void Tick();
	virtual void Frame() {}
	virtual void Touch(Entity& other) {}

	void Delete();

	friend class Game;
protected:
	virtual ~Entity() = default;

	float m_angle;
	float m_angularVelocity;
	Vector2 m_position;
	Vector2 m_BBox;
	Vector2 m_velocity;
	SDL_Texture* m_texture;
private:
	static void CheckCollisions();
	static void ClearList();
	static void UpdateList();

	bool m_isDeleted = false;
	static std::vector<Entity*> s_new;
	static std::vector<Entity*> s_all;
};