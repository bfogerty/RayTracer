#ifndef __COLOR__
#define __COLOR__
#include <memory.h>
#include <algorithm>

class Color
{
public:

	enum RGBA
	{
		r = 0,
		g = 1,
		b = 2,
		a = 3,
	};

	Color()
	{
		memset(values, 0, sizeof(unsigned int) * 4);
	}

	Color(float t)
	{
		std::fill(values, values + 4, t);
	}

	Color(const Color& other)
	{
		memcpy(values, (void*)(other.values), sizeof(float) * 4);
	}

	Color operator =(const Color& other)
	{
		Color result;
		memcpy(result.values, (void*)(other.values), sizeof(float) * 4);

		return result;
	}

	Color(float r, float g, float b)
	{
		values[0] = r;
		values[1] = g;
		values[2] = b;
		values[3] = 1.0f;
	}

	Color(float r, float g, float b, float a)
	{
		values[0] = r;
		values[1] = g;
		values[2] = b;
		values[3] = a;
	}

	void SetValues(float r, float g, float b, float a)
	{
		values[0] = r;
		values[1] = g;
		values[2] = b;
		values[3] = a;
	}

	void SetValues(float t)
	{
		std::fill(values, values + 4, t);
	}

	const float* GetValues()
	{
		return values;
	}

	static void Clamp(Color& color, float minValue, float maxValue)
	{
		if (color.values[0] < minValue) color.values[0] = minValue;
		if (color.values[0] > maxValue) color.values[0] = maxValue;

		if (color.values[1] < minValue) color.values[1] = minValue;
		if (color.values[1] > maxValue) color.values[1] = maxValue;

		if (color.values[2] < minValue) color.values[2] = minValue;
		if (color.values[2] > maxValue) color.values[2] = maxValue;

		if (color.values[3] < minValue) color.values[3] = minValue;
		if (color.values[3] > maxValue) color.values[3] = maxValue;
	}

	static Color Lerp(const Color& lhs, const Color& rhs, const float& t)
	{
		float OneMinusT = 1.0f - t;
		Color result;
		result.values[r] = (OneMinusT * lhs.values[r]) + (t * rhs.values[r]);
		result.values[g] = (OneMinusT * lhs.values[g]) + (t * rhs.values[g]);
		result.values[b] = (OneMinusT * lhs.values[b]) + (t * rhs.values[b]);
		result.values[a] = (OneMinusT * lhs.values[a]) + (t * rhs.values[a]);

		return result;
	}

private:
	float values[4];
};

#endif