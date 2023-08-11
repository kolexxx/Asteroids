#pragma once

#include "Vector2.hpp"
class Matrix3x3
{
public:
	/// <summary>
	/// Creates a zero matrix.
	/// </summary>
	Matrix3x3();

	/// <summary>
	/// Creates an identity matrix multiplied by the given scalar.
	/// </summary>
	Matrix3x3(float scalar);

	static Matrix3x3 Ortho(float left, float right, float bottom, float top);
	static Matrix3x3 Rotation(float radians);
	static Matrix3x3 Scale(Vector2 vector);
	static Matrix3x3 Transform(Vector2 vector);

	void Print() const;
	[[nodiscard]] Matrix3x3 Transpose() const;

	inline float* operator[](unsigned int index) { return m_matrix[index]; }
	Matrix3x3 operator +(Matrix3x3& other);
	Matrix3x3 operator -(Matrix3x3& other);
	Matrix3x3 operator *(Matrix3x3& other);
	Vector2 operator *(Vector2& vector);
private:
	float m_matrix[3][3];
};