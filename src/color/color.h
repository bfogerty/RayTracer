#ifndef __COLOR__
#define __COLOR__
#include <memory.h>

class Color
{
public:

	Color()
	{
		memset(values, 0, sizeof(unsigned int) * 4);
	}

	Color(float t)
	{
		memset(values, t, sizeof(float) * 4);
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
		memset(values, t, sizeof(float) * 4);
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

private:
	float values[4];
};

#endif