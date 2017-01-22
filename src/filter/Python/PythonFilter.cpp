#include "PythonFilter.h"

void PythonFilter::Initialize()
{
	Py_Initialize();

	PyImport_ImportModule("sys");
	PyImport_ImportModule("numpy");
	PySys_SetPath(L".");

	m_ModuleName = PyUnicode_FromString("filter");
	m_PluginModule = PyImport_Import(m_ModuleName);
	//PyErr_Print();
	m_FilterFunc = PyObject_GetAttrString(m_PluginModule, "DoFilter");
	PyObject* args = PyTuple_Pack(0);
	PyObject* result = PyObject_CallObject(m_FilterFunc, args);
}

void PythonFilter::DoFilter()
{

}