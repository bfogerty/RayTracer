#include "renderer.h"
#include <thread>
#include <external/python/Python.h>
#include "utilities/StringHelper.h"

Renderer::Renderer(Config& config, int width, int height, int bytesPerPixel) 
	: m_Config(config)
	, m_Filter(nullptr)
	, m_Width(width)
	, m_Height(height)
	, m_BytesPerPixel(bytesPerPixel)
	, m_JobsCompleted(0)
	, m_Pixels(0)
{
	m_Pixels = new float[width * height * bytesPerPixel];

	if (m_Config.GetValue(Config::FILTER_TYPE) == "python")
	{
		m_Filter = new PythonFilter();
	}

	if (m_Filter != nullptr)
	{
		m_Filter->Initialize(m_Config);
	}
}

void Render_Thread(SoftwareFilter* filter, int* jobsCompleted, int startingX, int startingY, int endingX, int endingY, int width, int height, int bytesPerPixel, float* pixels)
{
	Color outputColor;
	for (int y = startingY; y < endingY; ++y)
	{
		for (int x = startingX; x < endingX; ++x)
		{
			filter->DoFilter(x, y, width, height, outputColor);

			int redIndex = (y*width*bytesPerPixel) + (x*bytesPerPixel + 0);
			memcpy(&pixels[redIndex], outputColor.GetValues(), sizeof(float) * bytesPerPixel);
		}
	}

	++(*jobsCompleted);
}

void Renderer::Render()
{
	if (m_Filter == nullptr)
	{
		return;
	}

	m_Filter->Render(m_Pixels, m_Width, m_Height, m_BytesPerPixel);
}

//void Renderer::Render()
//{
//	int jobsCompleted = 0;
//	Render_Thread(m_Filter, &jobsCompleted, 0, 0, m_Width, m_Height, m_Width, m_Height, m_BytesPerPixel, m_Pixels);
//}

//void Renderer::Render()
//{
//	int d = m_Width / 5;
//
//	std::thread t1(Render_Thread, m_Filter, &m_JobsCompleted, 0, 0, d, m_Height, m_Width, m_Height, m_BytesPerPixel, m_Pixels);
//	t1.detach();
//
//	std::thread t2(Render_Thread, m_Filter, &m_JobsCompleted, d, 0, d * 2, m_Height, m_Width, m_Height, m_BytesPerPixel, m_Pixels);
//	t2.detach();
//
//	std::thread t3(Render_Thread, m_Filter, &m_JobsCompleted, d * 2, 0, d * 3, m_Height, m_Width, m_Height, m_BytesPerPixel, m_Pixels);
//	t3.detach();
//
//	std::thread t4(Render_Thread, m_Filter, &m_JobsCompleted, d * 3, 0, d * 4, m_Height, m_Width, m_Height, m_BytesPerPixel, m_Pixels);
//	t4.detach();
//
//	std::thread t5(Render_Thread, m_Filter, &m_JobsCompleted, d * 4, 0, m_Width, m_Height, m_Width, m_Height, m_BytesPerPixel, m_Pixels);
//	t5.detach();
//
//	while (m_JobsCompleted < 5);
//}