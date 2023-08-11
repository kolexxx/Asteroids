#include "Vector2.hpp"

#include <math.h>

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::DistanceBetween(const Vector2& other) const
{
	return (*this - other).Length();
}

float Vector2::Length() const
{
	return sqrtf(x * x + y * y);
}

Vector2 Vector2::Normal() const
{
	const auto length = Length();

	return Vector2(x / length, y / length);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/( float scalar ) const
{
	return Vector2( x / scalar, y / scalar );
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

float Vector2::operator*(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

Vector2::operator SDL_FPoint()
{
	return *( SDL_FPoint* ) this;
}

std::ostream& operator<<( std::ostream& os, const Vector2& vector )
{
	os << '(' << vector.x << ',' << vector.y << ')';

	return os;
}
