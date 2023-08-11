#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <array>
#include <string>
#include <unordered_map>

class Sound
{
public:
	static void Init();
	static int32_t Play( const std::string& path, bool loop = false );
	static void Stop( int32_t channel );
	static void StopAll();
private:
	static std::unordered_map<std::string, Mix_Chunk*> s_chunks;
};