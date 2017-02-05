#include "PythonFilter.h"

void PythonFilter::Initialize()
{
	Py_Initialize();

	PyImport_ImportModule("sys");
	PyImport_ImportModule("numpy");
	PyImport_ImportModule("threading");
	PySys_SetPath(L".");

	m_ModuleName = PyUnicode_FromString("filter");
	m_PluginModule = PyImport_Import(m_ModuleName);
	PyErr_Print();
	m_FilterFunc = PyObject_GetAttrString(m_PluginModule, "DoFilter");

	CreateMainRenderMethod();
}

void PythonFilter::CreateMainRenderMethod()
{

}

void PythonFilter::Render(float *pixels, int width, int height, int bytesPerPixel)
{
	int d = width / 5;

	//FILE* file = fopen("renderer.py", "r");
	//PyRun_SimpleFile(file, "renderer.py");
	//fclose(file);

	PyObject* rendererName = PyUnicode_FromString("renderer");
	PyObject* rendererModule = PyImport_Import(rendererName);
	PyErr_Print();
	m_RenderFunc = PyObject_GetAttrString(rendererModule, "Render");
	
	int count = width*height*bytesPerPixel;
	PyObject *l = PyList_New(count);
	for (size_t i = 0; i < count; i++) {
		PyObject* value = PyFloat_FromDouble(0.0);
		PyList_SetItem(l, i, value);
	}

	PyObject* args = Py_BuildValue("Oiii", l, width, height, bytesPerPixel);
	PyErr_Print();
	PyObject* result = PyObject_CallObject(m_RenderFunc, args);
	PyErr_Print();

	int listSize = PyList_Size(result);

	for (int i = 0; i < listSize; ++i)
	{
		PyObject* value = PyList_GetItem(result, i);
		pixels[i] = PyFloat_AsDouble(value);
	}

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