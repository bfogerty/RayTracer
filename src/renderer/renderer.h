#ifndef __RENDERER__
#define __RENDERER__

#include "config.h"
#include "color/color.h"
#include "filter/SoftwareFilter.h"
#include "filter/Python/PythonFilter.h"

class Renderer
{
public:
	Renderer(Config& config, int width, int height, int bytesPerPixel);
	void Render();
	inline float* GetPixels() { return m_Pixels; }

private:

	Config m_Config;
	SoftwareFilter *m_Filter;
	int m_Width;
	int m_Height;
	int m_BytesPerPixel;
	int m_JobsCompleted;
	float *m_Pixels;
};

#endif