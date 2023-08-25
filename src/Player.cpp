#include "Player.hpp"

#include "Sound.hpp"
#include "Bullet.hpp"
#include "Input.hpp"
#include <sstream>
#include <math.h>

Player::Player() :
	Entity( Vector2( WINDOW_WIDTH, WINDOW_HEIGHT ) / 2.f, Vector2( 40, 40 ), -3.14f / 2.f ),
	m_lives( 3 ),
	m_score( 0 ),
	m_timeUntilCanFire( 0.f ),
	m_respawnTime( 0.f ),
	m_thrustSoundChannel( -1 )
{
}

Player::~Player()
{
	Game::s_player = nullptr;

	if ( m_thrustSoundChannel >= 0 )
	{
		Sound::Stop( m_thrustSoundChannel );
		m_thrustSoundChannel = -1;
	}
}

void Player::Tick()
{
	if ( !m_respawnTime )
		return;

	if ( Input::Down( 'A' ) )
		m_angularVelocity = -3.14f * 1.5f;
	else if ( Input::Down( 'D' ) )
		m_angularVelocity = 3.14f * 1.5f;
	else
		m_angularVelocity = 0.f;

	auto forward = Vector2( cosf( m_angle ), sinf( m_angle ) );
	auto force = Vector2();
	auto q = 0.8f;

	if ( Input::Down( 'W' ) )
	{
		force = forward * 400.f;

		if ( m_thrustSoundChannel < 0 )
			m_thrustSoundChannel = Sound::Play( "res/thrust.wav", true );
	}
	else if ( m_thrustSoundChannel >= 0 )
	{
		Sound::Stop( m_thrustSoundChannel );
		m_thrustSoundChannel = -1;
	}

	m_velocity = ( force - ( force - m_velocity * q ) * expf( -q * Time::Delta() ) ) * ( 1.0f / q );

	Entity::Tick();

	if ( m_timeUntilCanFire && Input::Pressed( ' ' ) )
	{
		new Bullet( this, m_position + forward * 5, m_angle );
		m_timeUntilCanFire = 0.1f;
	}
}

void Player::Frame()
{
	std::ostringstream out;
	out << "SCORE:" << m_score;

	Graphics::DrawText( out.str().c_str(), Vector2( 10, 5 ) );

	auto position = Vector2( 20, 50 );
	for ( auto i = 0; i < m_lives; i++ )
	{
		Vector2 points[] =
		{
			Vector2( 15.f, 0.f ),
			Vector2(),
			Vector2( 15.f * cosf( 4 * acosf( -1 ) / 3 ), 15.f * sinf( 4 * acosf( -1 ) / 3 ) )
		};

		Graphics::DrawTriangle( points, position, 0 );

		points[2].y *= -1;

		Graphics::DrawTriangle( points, position, 0 );

		position.x += 30;
	}

	if ( !m_respawnTime )
		return;

	Vector2 points[] =
	{
		Vector2( 20.f, 0.f ),
		Vector2(),
		Vector2( 20.f * cosf( 4 * acosf( -1 ) / 3 ), 20.f * sinf( 4 * acosf( -1 ) / 3 ) )
	};

	Graphics::DrawTriangle( points, m_position, m_angle );

	points[2].y *= -1;

	Graphics::DrawTriangle( points, m_position, m_angle );
}

void Player::Touch( Entity& other )
{
	if ( !m_respawnTime )
		m_respawnTime += Time::Delta();
}

void Player::TakeHit()
{
	if ( !m_respawnTime )
		return;

	if ( m_lives-- == 1 )
		Delete();
	else
		Reset();

	Sound::Play( "res/bangLarge.wav" );
}

void Player::Reset()
{
	m_respawnTime = 2.f;
	m_position = Vector2( WINDOW_WIDTH, WINDOW_HEIGHT ) / 2.f;
	m_angle = -3.14f / 2.f;
	m_velocity = Vector2();
	m_angularVelocity = 0.f;

	if ( m_thrustSoundChannel >= 0 )
	{
		Sound::Stop( m_thrustSoundChannel );
		m_thrustSoundChannel = -1;
	}
}

void Player::AddScore( uint32_t score )
{
	m_score += score;
}
