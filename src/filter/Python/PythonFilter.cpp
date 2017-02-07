#include "PythonFilter.h"

void PythonFilter::Initialize(Config &config)
{
	m_Config = config;

	Py_Initialize();

	PyImport_ImportModule("sys");
	PyImport_ImportModule("numpy");
	PyImport_ImportModule("threading");

	std::string ansiDirectory = m_Config.GetValue(Config::FILTER_DIRECTORY);
	std::wstring directory = std::wstring(ansiDirectory.begin(), ansiDirectory.end());

	PySys_SetPath(directory.c_str());

	m_ModuleName = PyUnicode_FromString("filter");
	m_PluginModule = PyImport_Import(m_ModuleName);
	PyErr_Print();
	m_FilterFunc = PyObject_GetAttrString(m_PluginModule, "DoFilter");

	CreateMainRenderMethod();
}

void PythonFilter::CreateMainRenderMethod()
{
	std::string renderModuleName = m_Config.GetValue(Config::RENDER_MODULE);
	PyObject* rendererName = PyUnicode_FromString(renderModuleName.c_str());
	PyObject* rendererModule = PyImport_Import(rendererName);
	PyErr_Print();
	m_RenderFunc = PyObject_GetAttrString(rendererModule, "Render");
}

void PythonFilter::Render(float *pixels, int width, int height, int bytesPerPixel)
{
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
		// Ensure that we clamp the final values in a 
		// range between 0.0 and 1.0 so we don't encounter
		// strange color artifacts.
		pixels[i] = clamp01(PyFloat_AsDouble(value));
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