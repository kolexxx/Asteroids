#include "Entity.hpp"

#include "Time.hpp"

Entity::Entity(Vector2 position, Vector2 BBox, float angle) :
	m_position(position),
	m_BBox(BBox),
	m_angle(angle),
	m_angularVelocity(0.f),
	m_isDead(false),
	m_texture(nullptr)
{
	s_new.push_back(this);
}

void Entity::Tick()
{
	//
	// Increase our position and angle by their respective velocities.
	//
	m_angle += m_angularVelocity * Time::Delta();
	m_position += m_velocity * Time::Delta();

	//
	// Screen wrapping.
	//
	auto halfWidth = m_BBox.x / 2.f;
	auto halfHeight = m_BBox.y / 2.f;

	if (m_position.x - halfWidth > WINDOW_WIDTH)
		m_position.x = -halfWidth;
	else if (m_position.x + halfWidth < 0)
		m_position.x = WINDOW_WIDTH + halfWidth;

	if (m_position.y - halfHeight > WINDOW_HEIGHT)
		m_position.y = -halfHeight;
	else if (m_position.y + halfHeight < 0)
		m_position.y = WINDOW_HEIGHT + halfHeight;
}

Vector2& Entity::Position()
{
	return m_position;
}

void Entity::Delete()
{
	m_isDeleted = true;
}

void Entity::CheckCollisions()
{
	for (int i = 0; i < s_all.size() - 1; i++)
	{
		for (int j = i + 1; j < s_all.size(); j++)
		{
			auto& entityA = *s_all[i];
			auto& entityB = *s_all[j];

			if (entityA.m_isDeleted || entityB.m_isDeleted)
				continue;

			if (entityA.m_isDead || entityB.m_isDead)
				continue;

			if (!entityA.IsTouching(entityB))
				continue;

			entityA.Touch(entityB);
			entityB.Touch(entityA);
		}
	}
}

void Entity::ClearList()
{
	for (auto* entity : s_all)
		delete entity;

	s_all.clear();

	for (auto* entity : s_new)
		delete entity;

	s_new.clear();
}

bool Entity::IsTouching(const Entity& other)
{
	auto maxLeft = std::max(m_position.x - m_BBox.x / 2.f, other.m_position.x - other.m_BBox.x / 2.f);
	auto minRight = std::min(m_position.x + m_BBox.x / 2.f, other.m_position.x + other.m_BBox.x / 2.f);

	if (maxLeft > minRight)
		return false;

	auto maxBottom = std::max(m_position.y - m_BBox.y / 2.f, other.m_position.y - other.m_BBox.y / 2.f);
	auto minTop = std::min(m_position.y + m_BBox.y / 2.f, other.m_position.y + other.m_BBox.y / 2.f);

	if (maxBottom > minTop)
		return false;

	return true;
}

void Entity::UpdateList()
{
	for (auto it = s_all.begin(); it != s_all.end(); it++)
	{
		if (!(*it)->m_isDeleted)
			continue;

		delete* it;
		it = s_all.erase(it);

		if (it == s_all.end())
			break;
	}

	s_all.insert(s_all.begin(), s_new.begin(), s_new.end());
	s_new.clear();
}

std::vector<Entity*> Entity::s_new = {};
std::vector<Entity*> Entity::s_all = {};