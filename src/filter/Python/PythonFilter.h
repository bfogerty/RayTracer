#ifndef __PYTHON_FILTER__
#define __PYTHON_FILTER__

#include "config.h"
#include <filter/SoftwareFilter.h>
#include <math/CommonMath.h>
#include <color/color.h>
#include <external/python/Python.h>

class PythonFilter : public SoftwareFilter
{
public:
	void Initialize(Config &config);

	void Render(float *pixels, int width, int height, int bytesPerPixel);

	void DoFilter(	const unsigned int& x, 
					const unsigned int& y, 
					const unsigned int& width, 
					const unsigned int& height, 
					Color& outputColor );

private:

	void CreateMainRenderMethod();

	Config m_Config;
	PyObject* m_ModuleName;
	PyObject* m_PluginModule;
	PyObject* m_FilterFunc;
	PyObject* m_RenderFunc;
};

#endif