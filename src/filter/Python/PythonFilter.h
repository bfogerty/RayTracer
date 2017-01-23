#ifndef __PYTHON_FILTER__
#define __PYTHON_FILTER__

#include <filter/SoftwareFilter.h>
#include <color/color.h>
#include <external/python/Python.h>

class PythonFilter : public SoftwareFilter
{
public:
	void Initialize();
	void DoFilter(	const unsigned int& x, 
					const unsigned int& y, 
					const unsigned int& width, 
					const unsigned int& height, 
					Color& outputColor);

private:
	PyObject* m_ModuleName;
	PyObject* m_PluginModule;
	PyObject* m_FilterFunc;

};

#endif