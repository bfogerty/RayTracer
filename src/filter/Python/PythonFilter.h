#ifndef __PYTHON_FILTER__
#define __PYTHON_FILTER__

#include <external/python/Python.h>

class PythonFilter
{
public:
	void Initialize();
	void DoFilter();

private:
	PyObject* m_ModuleName;
	PyObject* m_PluginModule;
	PyObject* m_FilterFunc;

};

#endif