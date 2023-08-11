#include "Input.hpp"

#include "Game.hpp"

bool Input::Pressed( char key )
{
	return s_pressed[key];
}

bool Input::Down( char key )
{
	return s_down[key];
}

bool Input::Released( char key )
{
	return s_released[key];
}

void Input::Build()
{
	SDL_Event event;

	for ( auto& b : s_released )
		b = false;

	for ( auto& b : s_pressed )
		b = false;

	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
			case SDL_EVENT_QUIT:
			{
				Game::Quit();
				return;
			}
			case SDL_EVENT_KEY_DOWN:
			{
				auto key = event.key.keysym.sym;

				if ( key >= SDLK_a && key <= SDLK_z )
					key = key - 'a' + 'A';

				if ( key > 'Z' )
					break;

				s_pressed[key] = !s_down[key] ? true : false;
				s_down[key] = true;
				s_released[key] = false;

				break;
			}
			case SDL_EVENT_KEY_UP:
			{
				auto key = event.key.keysym.sym;

				if ( key >= SDLK_a && key <= SDLK_z )
					key = key - 'a' + 'A';

				if ( key > 'Z' )
					break;

				s_pressed[key] = false;
				s_down[key] = false;
				s_released[key] = true;

				break;
			}
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			{
				Game::Quit();
			}
		}
	}
}

std::array<bool, 91> Input::s_pressed{};
std::array<bool, 91> Input::s_down{};
std::array<bool, 91> Input::s_released{};