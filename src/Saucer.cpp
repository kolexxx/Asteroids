#include "Saucer.hpp"
#include "Player.hpp"
#include "Sound.hpp"
#include "Bullet.hpp"
#include "Math/Matrix3x3.hpp"

Saucer::Saucer( bool small ) :
	m_direction( rand() & 1 ? Vector2::Right : Vector2::Left ),
	m_small( small ),
	m_timeUntilCanFire( 1.f ),
	Entity( Vector2(), Vector2( 60, 30 ) / ( small ? 2.f : 1.f ) )
{
	Game::s_numOfEnemies++;

	auto halfWidth = m_BBox.x / 2.f;

	m_position.x = m_direction == Vector2::Left ? WINDOW_WIDTH + halfWidth : -halfWidth;
	m_position.y = rand() % ( int ) WINDOW_HEIGHT;
	m_velocity = m_direction * 150.f;
	m_texture = Graphics::LoadTexture( "res/saucer.bmp" );
	m_sirenSound = Sound::Play( "res/saucerBig.wav", true );
}

Saucer::~Saucer()
{
	Game::s_numOfEnemies--;
	Game::s_saucer = nullptr;
	Game::s_timeUntilSaucerSpawn = 3.f + rand() % 5;

	Sound::Play( "res/bangLarge.wav" );
	Sound::Stop( m_sirenSound );
}

void Saucer::Tick()
{
	// Saucers disappear when they go off screen.
	auto halfWidth = m_BBox.x / 2.f;
	auto halfHeight = m_BBox.y / 2.f;

	if ( m_position.x - halfWidth > WINDOW_WIDTH || m_position.x + halfWidth < 0 )
	{
		Delete();
		return;
	}

	if ( m_position.y - halfHeight > WINDOW_HEIGHT )
		m_position.y = -halfHeight;
	else if ( m_position.y + halfHeight < 0 )
		m_position.y = WINDOW_HEIGHT + halfHeight;

	if ( m_timeUntilCanFire )
	{
		m_timeUntilCanFire = 1.f;
		new Bullet( this, m_position, rand() );
	}

	if ( rand() < 1000 )
	{
		auto angle = ( rand() % 3 - 1 ) * acosf( -1 ) / 4.f;
		m_velocity = Matrix3x3::Rotation( angle ) * m_direction * 150.f;
	}

	m_position = m_position + m_velocity * Time::Delta();
}

void Saucer::Frame()
{
	Graphics::DrawRect( m_BBox, m_position, acosf( -1 ), m_texture );
}

void Saucer::Touch( Entity& other )
{
	if ( &other != Game::s_player )
		return;

	Delete();
	other.TakeHit();
}

uint32_t Saucer::CalculateReward()
{
	return 200;
}

