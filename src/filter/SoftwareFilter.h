#ifndef __SOFTWARE_FILTER__
#define __SOFTWARE_FILTER__
#include <color/color.h>

class SoftwareFilter
{
public:
	virtual void Initialize() = 0;
	virtual void DoFilter(const unsigned int& x,
		const unsigned int& y,
		const unsigned int& width,
		const unsigned int& height,
		Color& outputColor) = 0;
};

#endif