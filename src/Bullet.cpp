#include "Bullet.hpp"

#include "Player.hpp"
#include "Asteroid.hpp"
#include "Game.hpp"
#include "Time.hpp"

Bullet::Bullet( Entity* owner, Vector2 position, float angle ) :
	m_owner( owner ),
	m_speed( WINDOW_WIDTH ),
	m_timeUntilDelete( 0.5f ),
	Entity( position, Vector2( 5, 5 ), angle )
{
	m_velocity = Vector2( cosf( m_angle ), sinf( m_angle ) ) * m_speed;
	Sound::Play( "res/fire.wav" );
}

void Bullet::Tick()
{
	Entity::Tick();

	if ( m_timeUntilDelete )
		Delete();
}

void Bullet::Frame()
{
	Graphics::DrawRect( m_BBox, m_position, m_angle );
}

void Bullet::Touch( Entity& other )
{
	if ( &other == m_owner )
		return;

	if ( m_owner == Game::s_player )
		Game::s_player->AddScore( other.CalculateReward() );

	Delete();
	other.TakeHit();
}
