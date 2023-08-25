#pragma once

#include <iostream>
#include <SDL.h>

class Vector2
{
public:
	static const Vector2 Right;
	static const Vector2 Left;
	static const Vector2 Up;
	static const Vector2 Down;

	float x, y;

	Vector2();
	Vector2( float x, float y );

	[[nodiscard]] float DistanceBetween( const Vector2& other ) const;
	[[nodiscard]] float Length() const;
	[[nodiscard]] Vector2 Normal() const;

	bool operator ==( const Vector2& other ) const;
	Vector2 operator *( float scalar ) const;
	Vector2 operator /( float scalar ) const;
	Vector2 operator +( const Vector2& other ) const;
	Vector2 operator -( const Vector2& other ) const;
	float operator *( const Vector2& other ) const;
	operator SDL_FPoint();

	friend std::ostream& operator<<( std::ostream& os, const Vector2& dt );
};