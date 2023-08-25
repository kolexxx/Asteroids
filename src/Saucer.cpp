#include "Saucer.hpp"
#include "Sound.hpp"
#include "Bullet.hpp"

Saucer::Saucer( bool small ) :
	m_small( small ),
	m_timeUntilCanFire( 1.f ),
	Entity( Vector2(), Vector2( 60, 30 ), rand() & 1 ? 0 : acosf( -1 ) )
{
	Game::s_numOfEnemies++;

	auto halfWidth = m_BBox.x / 2.f;

	m_position.x = m_angle != 0.f ? WINDOW_WIDTH + halfWidth : -halfWidth;
	m_position.y = rand() % ( int ) WINDOW_HEIGHT;
	m_velocity = m_angle == 0.f ? Vector2( 1, 0 ) : Vector2( -1, 0 );
	m_velocity = m_velocity * 100.f;

	m_texture = Graphics::LoadTexture( "res/saucer.bmp" );
	m_sirenSound = Sound::Play( "res/saucerBig.wav", true );
}

Saucer::~Saucer()
{
	Game::s_numOfEnemies--;
	Game::s_saucer = nullptr;
	Game::s_timeUntilSaucerSpawn = 6.f;

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
		auto angle = m_angle + ( rand() % 90 - 45 ) * acos( -1 ) / 180.f;
		m_velocity = Vector2( cosf( angle ), sinf( angle ) ) * 100.f;
	}

	m_position = m_position + m_velocity * Time::Delta();
}

void Saucer::Frame()
{
	Graphics::DrawRect( m_BBox, m_position, acosf( -1 ), m_texture );
}

uint32_t Saucer::CalculateReward()
{
	return 200;
}

