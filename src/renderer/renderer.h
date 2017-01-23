#ifndef __RENDERER__
#define __RENDERER__
#include "color/color.h"
#include "filter/SoftwareFilter.h"

class Renderer
{
public:
	Renderer(SoftwareFilter* filter, int width, int height, int bytesPerPixel);
	void Render();
	inline float* GetPixels() { return m_Pixels; }

private:

	SoftwareFilter *m_Filter;
	int m_Width;
	int m_Height;
	int m_BytesPerPixel;
	int m_JobsCompleted;
	float *m_Pixels;
};

#endif