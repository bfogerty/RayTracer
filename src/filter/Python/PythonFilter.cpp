#include "PythonFilter.h"

void PythonFilter::Initialize()
{
	Py_Initialize();

	PyImport_ImportModule("sys");
	PyImport_ImportModule("numpy");
	PySys_SetPath(L".");

	m_ModuleName = PyUnicode_FromString("filter");
	m_PluginModule = PyImport_Import(m_ModuleName);
	PyErr_Print();
	m_FilterFunc = PyObject_GetAttrString(m_PluginModule, "DoFilter");
}

void PythonFilter::DoFilter(const unsigned int& x, 
							const unsigned int& y, 
							const unsigned int& width, 
							const unsigned int& height, 
							Color& outputColor)
{
	outputColor.SetValues(0.0f);

	PyObject* args = Py_BuildValue("iiii", x, y, width, height);
	PyObject* result = PyObject_CallObject(m_FilterFunc, args);

	float tupleValues[4];
	PyArg_ParseTuple(result, "ffff", &tupleValues[0], &tupleValues[1], &tupleValues[2], &tupleValues[3]);

	outputColor.SetValues(tupleValues);
}