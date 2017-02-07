#ifndef __COMMON_MATH__
#define __COMMON_MATH__

inline float clamp(float value, float min, float max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}

inline float clamp01(float value)
{
	return clamp(value, 0.000f, 1.0f);
}


#endif