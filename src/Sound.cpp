#include "Sound.hpp"
#include <SDL.h>
void Sound::Init()
{
	SDL_AudioSpec spec;

	/* Initialize variables */
	spec.freq = MIX_DEFAULT_FREQUENCY;
	spec.format = SDL_AUDIO_S8;
	spec.channels = MIX_DEFAULT_CHANNELS;

	Mix_OpenAudio( 0, &spec );
}

int32_t Sound::Play( const std::string& path, bool loop )
{
	Mix_Chunk* chunk = nullptr;

	auto it = s_chunks.find( path );

	if ( it == s_chunks.end() )
	{
		chunk = Mix_LoadWAV( path.c_str() );
		chunk->volume = 10;

		s_chunks[path] = chunk;
	}
	else
	{
		chunk = it->second;
	}

	return Mix_PlayChannel( -1, chunk, loop ? -1 : 0 );
}

void Sound::Stop( int32_t channel )
{
	Mix_HaltChannel( channel );
}

void Sound::StopAll()
{
	for ( auto channel = 0; channel < MIX_CHANNELS; channel++ )
		Mix_HaltChannel( channel );
}

std::unordered_map<std::string, Mix_Chunk*> Sound::s_chunks = {};