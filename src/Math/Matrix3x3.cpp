#include "Matrix3x3.hpp"

#include <stdio.h>
#include <math.h>

Matrix3x3::Matrix3x3()
{
	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			m_matrix[i][j] = 0;
		}
	}
}

Matrix3x3::Matrix3x3(float scalar) : Matrix3x3()
{
	for (auto i = 0; i < 3; i++)
		m_matrix[i][i] = scalar;
}

Matrix3x3 Matrix3x3::Ortho(float left, float right, float bottom, float top)
{
	auto result = Matrix3x3(1);

	result[0][0] = 2.0f / (right - left);
	result[0][2] = (right + left) / (right - left);
	result[1][1] = 2.0f / (top - bottom);
	result[1][2] = (top + bottom) / (top - bottom);

	return result;
}

Matrix3x3 Matrix3x3::Rotation(float radians)
{
	auto result = Matrix3x3(1);

	auto sin = sinf(radians);
	auto cos = cosf(radians);

	result[0][0] = cos;
	result[0][1] = -sin;
	result[1][0] = sin;
	result[1][1] = cos;

	return result;
}

Matrix3x3 Matrix3x3::Scale(Vector2 vector)
{
	auto result = Matrix3x3(1);

	result[0][0] = vector.x;
	result[1][1] = vector.y;

	return result;
}

Matrix3x3 Matrix3x3::Transform(Vector2 vector)
{
	auto result = Matrix3x3(1);

	result[0][2] = vector.x;
	result[1][2] = vector.y;

	return result;
}

void Matrix3x3::Print() const
{
	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			printf("%f ", m_matrix[i][j]);
		}
		printf("\n");
	}
}

Matrix3x3 Matrix3x3::Transpose() const
{
	auto result = Matrix3x3();

	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			result[i][j] = m_matrix[j][i];
		}
	}

	return result;
}

Matrix3x3 Matrix3x3::operator+(Matrix3x3& other)
{
	auto result = Matrix3x3();

	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			result[i][j] = m_matrix[i][j] + other[i][j];
		}
	}

	return result;
}

Matrix3x3 Matrix3x3::operator-(Matrix3x3& other)
{
	auto result = Matrix3x3();

	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			result[i][j] = m_matrix[i][j] - other[i][j];
		}
	}

	return result;
}

Matrix3x3 Matrix3x3::operator*(Matrix3x3& other)
{
	auto result = Matrix3x3();

	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			for (auto k = 0; k < 3; k++)
			{
				result[i][j] += m_matrix[i][k] * other[k][j];
			}
		}
	}

	return result;
}

Vector2 Matrix3x3::operator*(Vector2& vector)
{
	auto result = Vector2();

	result.x = vector.x * m_matrix[0][0] + vector.y * m_matrix[0][1] + m_matrix[0][2];
	result.y = vector.x * m_matrix[1][0] + vector.y * m_matrix[1][1] + m_matrix[1][2];

	return result;
}
