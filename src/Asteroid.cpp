#include "Asteroid.hpp"

#include "Time.hpp"
#include "Sound.hpp"

Asteroid& Asteroid::SpawnFromEdge()
{
	auto& asteroid = *new Asteroid( 3 );

	bool horizontal = rand() & 1;
	bool max = rand() & 1;

	if ( horizontal )
	{
		auto halfWidth = asteroid.m_BBox.x / 2.f;

		asteroid.m_position.x = max ? WINDOW_WIDTH + halfWidth : -halfWidth;
		asteroid.m_position.y = rand() % ( int ) WINDOW_HEIGHT;
	}
	else
	{
		auto halfHeight = asteroid.m_BBox.y / 2.f;

		asteroid.m_position.y = max ? WINDOW_HEIGHT + halfHeight : -halfHeight;
		asteroid.m_position.x = rand() % ( int ) WINDOW_WIDTH;
	}

	return asteroid;
}

Asteroid::Asteroid( int level ) :
	Entity( Vector2(), Vector2( 30, 30 )* level, rand() % 360 ),
	m_level( level )
{
	NumOfAsteroids++;
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
	m_velocity = Vector2( WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f ) - m_position;
	m_velocity = m_velocity + Vector2( rand() % 200 - 100, rand() % 200 - 100 );
	m_velocity = m_velocity.Normal() * 50.f * ( 4 - m_level );
}

Asteroid::~Asteroid()
{
	NumOfAsteroids--;

	if ( Game::s_player == nullptr )
		return;

	Sound::Play( BoomSounds[m_level - 1] );

	if ( m_level <= 1 )
		return;

	( new Asteroid( m_level - 1 ) )->m_position = m_position;
	( new Asteroid( m_level - 1 ) )->m_position = m_position;
}

void Asteroid::Frame()
{
	Graphics::DrawRect( m_BBox, m_position, m_angle, m_texture );
}

uint32_t Asteroid::NumOfAsteroids = 0;
std::vector<SDL_Texture*> Asteroid::Textures = {};
std::vector<std::string> Asteroid::BoomSounds =
{
	"res/bangSmall.wav",
	"res/bangMedium.wav",
	"res/bangLarge.wav"
};