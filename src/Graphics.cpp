#include "Graphics.hpp"

#include "Game.hpp"
#include "Math/Matrix3x3.hpp" 

void Graphics::Init()
{
	s_renderer = SDL_CreateRenderer( Game::Window(), nullptr, SDL_RENDERER_ACCELERATED );

	TTF_Init();
	s_font = TTF_OpenFont( "res/font.ttf", 36 );
}

void Graphics::Clear()
{
	SDL_SetRenderDrawColor( s_renderer, 0, 0, 0, 255 );
	SDL_RenderClear( s_renderer );
}

void Graphics::Present()
{
	SDL_RenderPresent( s_renderer );
}

void Graphics::DrawText( const char* text, Vector2 pos, bool centerAtPos )
{
	auto* surface = TTF_RenderText_Solid( s_font, text, { 255,255,255, 255 } );
	auto* texture = SDL_CreateTextureFromSurface( s_renderer, surface );
	SDL_FRect dest = { pos.x, pos.y, surface->w,surface->h };

	if ( centerAtPos )
	{
		dest.x -= surface->w / 2.f;
		dest.y -= surface->h / 2.f;
	}

	SDL_RenderTexture( s_renderer, texture, nullptr, &dest );
	SDL_DestroyTexture( texture );
	SDL_DestroySurface( surface );
}

void Graphics::DrawRect( Vector2 dim, Vector2 position, float angle, SDL_Texture* texture )
{
	SDL_SetRenderDrawColor( s_renderer, 255, 255, 255, 255 );

	auto halfWidth = dim.x / 2.f;
	auto halfHeight = dim.y / 2.f;

	Vector2 points[4] =
	{
		{halfWidth, halfHeight},
		{halfWidth, -halfHeight},
		{-halfWidth, halfHeight},
		{ -halfWidth, -halfHeight }
	};

	auto rotation = Matrix3x3::Rotation( angle );
	auto transform = Matrix3x3::Transform( position );
	auto matrix = transform * rotation;

	SDL_Vertex vertices[4] =
	{
		{matrix * points[0], {255, 255, 255, 255}, {0, 0}},
		{matrix * points[1], {255, 255, 255, 255}, {0, 1}},
		{matrix * points[2], {255, 255, 255, 255}, {1, 0}},
		{matrix * points[3], {255, 255, 255, 255}, {1, 1}}
	};

	int indices[6] = { 0, 1, 2, 1, 2 ,3 };

	SDL_RenderGeometry( s_renderer, texture, vertices, 4, indices, 6 );
}

void Graphics::DrawTriangle( Vector2 points[3], Vector2 position, float angle)
{
	SDL_SetRenderDrawColor( s_renderer, 255, 255, 255, 255 );

	auto rotation = Matrix3x3::Rotation( angle );
	auto transform = Matrix3x3::Transform( position );
	auto matrix = transform * rotation;

	SDL_Vertex vertices[3] =
	{
		{matrix * points[0], {255, 255, 255, 255}, {1, 1}},
		{matrix * points[1], {255, 255, 255, 255}, {1, 1}},
		{matrix * points[2], {255, 255, 255, 255}, {1, 1}}
	};

	SDL_RenderGeometry( s_renderer, nullptr, vertices, 3, nullptr, 0 );
}

SDL_Texture* Graphics::LoadTexture( const char* path )
{
	auto* surface = SDL_LoadBMP( path );
	auto* texture = SDL_CreateTextureFromSurface( s_renderer, surface );

	SDL_DestroySurface( surface );

	return texture;
}

SDL_Renderer* Graphics::s_renderer = nullptr;
TTF_Font* Graphics::s_font = nullptr;