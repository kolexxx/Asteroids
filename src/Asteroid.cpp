#include "Asteroid.hpp"

#include "Time.hpp"
#include "Sound.hpp"

Asteroid::Asteroid( int level ) :
	Entity( Vector2(), Vector2( 30, 30 )* level, rand() % 360 ),
	m_level( level )
{
	Game::s_numOfEnemies++;
	m_texture = Textures[rand() % Textures.size()];

	bool horizontal = rand() & 1;
	bool max = rand() & 1;

	if ( horizontal )
	{
		auto halfWidth = m_BBox.x / 2.f;

		m_position.x = max ? WINDOW_WIDTH + halfWidth : -halfWidth;
		m_position.y = rand() % ( int ) WINDOW_HEIGHT;
	}
	else
	{
		auto halfHeight = m_BBox.y / 2.f;

		m_position.y = max ? WINDOW_HEIGHT + halfHeight : -halfHeight;
		m_position.x = rand() % ( int ) WINDOW_WIDTH;
	}

	m_angularVelocity = float( rand() % 100 ) / 50.f - 1.f;
	m_velocity = m_velocity + Vector2( rand() % 200 - 100, rand() % 200 - 100 );
	m_velocity = m_velocity.Normal() * 50.f * ( 4 - m_level );
}

Asteroid::~Asteroid()
{
	Game::s_numOfEnemies--;

	if ( Game::s_player == nullptr )
		return;

	Sound::Play( s_boomSounds[m_level - 1] );

	//
	// Spawn two asteroids one level lower if aren't
	// the smallest asteroid.
	//
	if ( m_level <= 1 )
		return;

	( new Asteroid( m_level - 1 ) )->m_position = m_position;
	( new Asteroid( m_level - 1 ) )->m_position = m_position;
}

void Asteroid::Frame()
{
	Graphics::DrawRect( m_BBox, m_position, m_angle, m_texture );
}

void Asteroid::Touch( Entity& other )
{
	// Don't collide with another asteroid.
	if ( dynamic_cast< Asteroid* >( &other ) != nullptr )
		return;

	Delete();
	other.TakeHit();
}

uint32_t Asteroid::CalculateReward()
{
	if ( m_level == 3 )
		return 20;
	else if ( m_level == 2 )
		return 50;
	else
		return 100;
}

std::vector<SDL_Texture*> Asteroid::Textures = {};
std::vector<std::string> Asteroid::s_boomSounds =
{
	"res/bangSmall.wav",
	"res/bangMedium.wav",
	"res/bangLarge.wav"
};