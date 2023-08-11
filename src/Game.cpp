#include "Game.hpp"

#include "Entity.hpp"
#include "Player.hpp"
#include "Graphics.hpp"
#include "Time.hpp"
#include "Input.hpp"
#include "Asteroid.hpp"
#include "Sound.hpp"

void Game::Start()
{
	SDL_Init( SDL_INIT_EVERYTHING );
	s_window = SDL_CreateWindow( "Asteroids", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL );

	Graphics::Init();
	Sound::Init();
	
	Asteroid::Textures =
	{
		Graphics::LoadTexture( "res/asteroid1.bmp" ),
		Graphics::LoadTexture( "res/asteroid2.bmp" ),
		Graphics::LoadTexture( "res/asteroid3.bmp" )
	};

	s_isRunning = true;
	Loop();
}

const uint32_t tickTime = 1000 / 60;
uint32_t lastTime = 0;
uint32_t elapsedTime = 0;

void Game::Loop()
{
	auto timeUntilAsteroidSpawn = TimeUntil();
	srand( Time::Ticks() );

	while ( s_isRunning )
	{
		lastTime = Time::Ticks();

		Input::Build();
		Graphics::Clear();

		if ( s_player == nullptr )
		{
			Graphics::DrawText( "PRESS SPACE TO START", Vector2( WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f ), true );

			if ( Input::Pressed( ' ' ) )
			{
				Entity::ClearList();
				s_player = new Player();
				timeUntilAsteroidSpawn = 0.f;
			}
		} 
		else
		{
			if ( timeUntilAsteroidSpawn && Asteroid::NumOfAsteroids < MAX_ASTEROIDS )
			{
				new Asteroid( 3 );
				timeUntilAsteroidSpawn = 5.f;
			}

			Entity::UpdateList();
			Entity::CheckCollisions();

			for ( auto* entity : Entity::All() )
				entity->Tick();

			for ( auto* entity : Entity::All() )
				entity->Frame();
		}

		Graphics::Present();
		elapsedTime = Time::Ticks() - lastTime;

		if ( tickTime > elapsedTime )
		{
			SDL_Delay( tickTime - elapsedTime );
		}

		Time::s_delta = ( Time::Ticks() - lastTime ) / 1000.f;
	}
}

void Game::Quit()
{
	SDL_DestroyWindow( s_window );
	SDL_DestroyRenderer( Graphics::s_renderer );
	SDL_Quit();
	s_isRunning = false;
}

bool Game::s_isRunning;
SDL_Window* Game::s_window = nullptr;
Player* Game::s_player = nullptr;