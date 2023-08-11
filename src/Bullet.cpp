#include "Bullet.hpp"

#include "Player.hpp"
#include "Asteroid.hpp"
#include "Game.hpp"
#include "Time.hpp"

Bullet::Bullet( Vector2 position, float angle ) :
	Entity( position, Vector2( 5, 5 ), angle ),
	m_speed( WINDOW_WIDTH ),
	m_timeUntilDelete( 1.f )
{
	m_velocity = Vector2( cosf( m_angle ), sinf( m_angle ) ) * m_speed;
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
	auto* asteroid = dynamic_cast< Asteroid* >( &other );

	if ( asteroid == nullptr )
		return;

	Game::s_player->AddScore( 10 );

	Delete();
	asteroid->Delete();
}
