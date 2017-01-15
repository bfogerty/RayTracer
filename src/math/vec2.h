#ifndef __VEC3__
#define __VEC3__
#include <memory.h>
#include <math.h>

class Vec2
{
	const int ValueSize = sizeof(float) * 2;

public:

	enum XYZ
	{
		x = 0,
		y = 1
	};

	Vec2()
	{
		memset(values, 0.0f, ValueSize);
	}

	Vec2(float xVal, float yVal)
	{
		values[x] = xVal;
		values[y] = yVal;
	}

	Vec2(const Vec2& other)
	{
		memcpy(values, other.values, ValueSize);
	}

	Vec2 operator +(const Vec2& rhs)
	{
		Vec2 result(values[x] + rhs.values[x],
					values[y] + rhs.values[y]);

		return result;

	}

	Vec2 operator +(const float& rhs)
	{
		Vec2 result(values[x] + rhs,
			values[y] + rhs);

		return result;

	}

	Vec2 operator -(const Vec2& rhs)
	{
		Vec2 result(values[x] - rhs.values[x],
					values[y] - rhs.values[y]);

		return result;

	}

	Vec2 operator -(const float& rhs)
	{
		Vec2 result(values[x] - rhs,
			values[y] - rhs);

		return result;

	}

	Vec2 operator *(const float& rhs)
	{
		Vec2 result(values[x] * rhs,
					values[y] * rhs);

		return result;

	}

	Vec2 operator /(const float& rhs)
	{
		Vec2 result(values[x] / rhs,
					values[y] / rhs);

		return result;
	}

	float MagnitudeSqaured()
	{
		float result =
			values[x] * values[x] +
			values[y] * values[y];

		return result;
	}

	float Magnitude()
	{
		float result = sqrt(
			values[x] * values[x] +
			values[y] * values[y]
			);

		return result;
	}

	float InverseMagnitude()
	{
		float result = sqrt(
			values[x] * values[x] +
			values[y] * values[y]
			);

		return 1.0f / result;
	}

	float InverseMagnitudeSquared()
	{
		float result =
			values[x] * values[x] +
			values[y] * values[y];

		return 1.0f / result;
	}

	void Normalize()
	{
		float invMagnitude = InverseMagnitude();

		values[x] = values[x] * invMagnitude;
		values[y] = values[y] * invMagnitude;
	}

	Vec2 GetNormalized()
	{
		float invMagnitude = InverseMagnitude();

		return Vec2(values[x] * invMagnitude, values[y] * invMagnitude);
	}

	float* GetValues()
	{
		return values;
	}

	inline float& X()
	{
		return values[x];
	}

	inline float& Y()
	{
		return values[y];
	}

	static float Dot(Vec2 lhs, Vec2 rhs)
	{
		float result =	lhs.values[x] * rhs.values[x] +
						lhs.values[y] * rhs.values[y];

		return result;
	}

	static Vec2 Project(Vec2 a, Vec2 b)
	{
		Vec2 result = b * (Vec2::Dot(a,b) * b.InverseMagnitudeSquared());

		return result;
	}

	static float Length(Vec2 lhs, Vec2 rhs)
	{
		float result = sqrt(
			lhs.values[x] * rhs.values[x] +
			lhs.values[y] * rhs.values[y]
			);

		return result;
	}


private:
	float values[2];
};

#endif