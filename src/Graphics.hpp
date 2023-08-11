#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Math/Vector2.hpp"

class Graphics
{
public:
	static void Init();
	static void Clear();
	static void Present();

	static void DrawText( const char* text, Vector2 position, bool centerAtPos = false );
	static void DrawRect( Vector2 dim, Vector2 pos, float angle, SDL_Texture* texture = nullptr );
	static void DrawTriangle( Vector2 points[3], Vector2 position, float angle);
	static SDL_Texture* LoadTexture( const char* path );

private:
	static SDL_Renderer* s_renderer;
	static TTF_Font* s_font;

	friend class Game;
};