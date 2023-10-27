#include "Saucer.hpp"
#include "Player.hpp"
#include "Sound.hpp"
#include "Bullet.hpp"
#include "Math/Matrix3x3.hpp"

Saucer::Saucer(bool small) :
	m_direction(rand() & 1 ? Vector2::UnitX : -Vector2::UnitX),
	m_small(small),
	m_timeUntilCanFire(1.f),
	Entity(Vector2(), Vector2(60, 30) / (small ? 2.f : 1.f))
{
	Game::s_numOfEnemies++;

	auto halfWidth = m_BBox.x / 2.f;

	//
	// Saucers appear at one end of the screen and move towards the other.
	//
	m_position.x = m_direction == Vector2::UnitX ? -halfWidth : WINDOW_WIDTH + halfWidth;
	m_position.y = rand() % (int)WINDOW_HEIGHT;
	m_velocity = m_direction * 150.f;

	m_texture = Graphics::LoadTexture("res/saucer.bmp");
	m_sirenSound = Sound::Play(m_small ? "res/saucerSmall.wav" : "res/saucerBig.wav", true);
}

Saucer::~Saucer()
{
	Game::s_numOfEnemies--;
	Game::s_saucer = nullptr;
	Game::s_timeUntilSaucerSpawn = 3.f + rand() % 5;

	Sound::Stop(m_sirenSound);

	if (m_isDead)
		Sound::Play("res/bangLarge.wav");
}

void Saucer::Tick()
{
	//
	// Saucers disappear when they go off screen horizontally.
	//
	auto halfWidth = m_BBox.x / 2.f;
	auto halfHeight = m_BBox.y / 2.f;

	if (m_position.x - halfWidth > WINDOW_WIDTH || m_position.x + halfWidth < 0)
	{
		Delete();
		return;
	}

	//
	// They wrap around the screen vertically.
	//
	if (m_position.y - halfHeight > WINDOW_HEIGHT)
		m_position.y = -halfHeight;
	else if (m_position.y + halfHeight < 0)
		m_position.y = WINDOW_HEIGHT + halfHeight;

	if (m_timeUntilCanFire)
	{
		m_timeUntilCanFire = 1.f;

		auto angle = static_cast<float>(rand());

		//
		// The small saucer aims at the player. It gets increasingly more
		// accurate as the player progresses.
		//
		if (m_small && !Game::s_player->IsRespawning())
		{
			auto dir = Game::s_player->Position() - m_position;
			auto tan = 1.f - std::min(1.f, float(Game::s_player->GetScore()) / 20000.f);

			tan *= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) * 2 - 1;
			dir += dir.Right() * tan * (rand() & 1 ? -1.f : 1.f);
			angle = atan2f(dir.y, dir.x);
		}

		new Bullet(this, m_position, angle);
	}

	//
	// The saucer decides if it wants to just go forward or also 45 degrees up or down.
	//
	if (rand() < 1000)
	{
		auto angle = (rand() % 3 - 1) * acosf(-1) / 4.f;
		m_velocity = Matrix3x3::Rotation(angle) * m_direction * 150.f;
	}

	m_position += m_velocity * Time::Delta();
}

void Saucer::Frame()
{
	Graphics::DrawRect(m_BBox, m_position, acosf(-1), m_texture);
}

void Saucer::Touch(Entity& other)
{
	if (&other != Game::s_player)
		return;

	m_isDead = true;

	Delete();
	other.TakeHit();
}

uint32_t Saucer::CalculateReward()
{
	return 200;
}

