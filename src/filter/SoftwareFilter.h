#ifndef __SOFTWARE_FILTER__
#define __SOFTWARE_FILTER__
#include "config.h"
#include <color/color.h>

class SoftwareFilter
{
public:
	virtual void Initialize(Config& config) = 0;

	virtual void Render(float *pixels, int width, int height, int bytesPerPixel) = 0;

	virtual void DoFilter(const unsigned int& x,
		const unsigned int& y,
		const unsigned int& width,
		const unsigned int& height,
		Color& outputColor) = 0;
};

#endif