#include "Player.hpp"

#include "Sound.hpp"
#include "Bullet.hpp"
#include "Input.hpp"
#include <sstream>
#include <math.h>

Player::Player() :
	Entity(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f, Vector2(40, 40), -3.14f / 2.f),
	m_lives(3),
	m_score(0),
	m_timeUntilCanFire(0.f),
	m_respawnTime(0.f),
	m_thrustSoundChannel(-1)
{
}

Player::~Player()
{
	Game::s_player = nullptr;

	if (m_thrustSoundChannel >= 0)
	{
		Sound::Stop(m_thrustSoundChannel);
		m_thrustSoundChannel = -1;
	}
}

void Player::Tick()
{
	// We are respawning, we shouldn't do any logic.
	if (!m_respawnTime)
		return;

	m_isDead = false;

	//
	// The ship changes it's rotation by pressing A or D. We set
	// the angular velocity so the angle changes by the delta time.
	//
	if (Input::Down('A'))
		m_angularVelocity = -3.14f * 1.5f;
	else if (Input::Down('D'))
		m_angularVelocity = 3.14f * 1.5f;
	else
		m_angularVelocity = 0.f;

	// Get the direction we want to move at.
	auto forward = Vector2(m_angle);

	// The force that will be applied to the ship.
	auto force = Vector2();

	// The coefficient for the drag of the ship.
	auto q = 0.8f;

	//
	// If we are pressing W, we want to apply for force in the
	// direction we want to move. Also play a sound for the force.
	//
	if (Input::Down('W'))
	{
		force = forward * 400.f;

		if (m_thrustSoundChannel < 0)
			m_thrustSoundChannel = Sound::Play("res/thrust.wav", true);
	}
	else if (m_thrustSoundChannel >= 0)
	{
		Sound::Stop(m_thrustSoundChannel);
		m_thrustSoundChannel = -1;
	}
	
	//
	// The solution for v in the equation m*a = F - q * v, where a is the acceleration, v the velocity
	// and F the force being applied. There is also drag which is proportional to the velocity.
	//
	m_velocity = (force - (force - m_velocity * q) * expf(-q * Time::Delta())) * (1.0f / q);

	// Apply our velocities and check to screenwrap.
	Entity::Tick();

	//
	// Fire a bullet in the direction we are facing 
	// if we pressed the spacebar.
	//
	if (m_timeUntilCanFire && Input::Pressed(' '))
	{
		new Bullet(this, m_position + forward * 5, m_angle);
		m_timeUntilCanFire = 0.1f;
	}
}

void Player::Frame()
{
	std::ostringstream out;
	out << "SCORE:" << m_score;

	Graphics::DrawText(out.str().c_str(), Vector2(10, 5));

	auto position = Vector2(20, 50);
	for (auto i = 0; i < m_lives; i++)
	{
		Vector2 points[] =
		{
			Vector2(15.f, 0.f),
			Vector2(),
			Vector2(15.f * cosf(4 * acosf(-1) / 3), 15.f * sinf(4 * acosf(-1) / 3))
		};

		Graphics::DrawTriangle(points, position, 0);

		points[2].y *= -1;

		Graphics::DrawTriangle(points, position, 0);

		position.x += 30;
	}

	if (!m_respawnTime)
		return;

	Vector2 points[] =
	{
		Vector2(20.f, 0.f),
		Vector2(),
		Vector2(20.f * cosf(4 * acosf(-1) / 3), 20.f * sinf(4 * acosf(-1) / 3))
	};

	Graphics::DrawTriangle(points, m_position, m_angle);

	points[2].y *= -1;

	Graphics::DrawTriangle(points, m_position, m_angle);
}

void Player::Touch(Entity& other)
{
	//
	// If we touched any other entity, increase our respawn time.
	//
	if (!m_respawnTime)
		m_respawnTime += 1.f;
}

void Player::TakeHit()
{
	if (!m_respawnTime)
		return;

	m_isDead = true;

	if (m_lives-- == 1)
		Delete();
	else
		Reset();

	Sound::Play("res/bangLarge.wav");
}

void Player::Reset()
{
	m_respawnTime = 2.f;
	m_position = Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f;
	m_angle = -3.14f / 2.f;
	m_velocity = Vector2();
	m_angularVelocity = 0.f;

	if (m_thrustSoundChannel >= 0)
	{
		Sound::Stop(m_thrustSoundChannel);
		m_thrustSoundChannel = -1;
	}
}

void Player::AddScore(uint32_t score)
{
	auto oldScore = m_score;
	m_score += score;

	//
	// The player earns an extra life every 10000 points.
	//
	if (oldScore / 10000 != m_score / 10000)
	{
		m_lives++;
		Sound::Play("res/extraShip.wav");
	}
}

bool Player::IsRespawning()
{
	return !m_respawnTime;
}

uint32_t Player::GetScore()
{
	return m_score;
}
