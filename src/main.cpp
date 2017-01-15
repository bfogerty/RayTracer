#include <iostream>
#include <math.h>
#include <algorithm>
#include <thread>
#include "math/vec2.h"
#include "color/color.h"
#include "time/StopWatch.h"
#include "export/PPMExporter.h"
using namespace std;


float clamp(float value, float min, float max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}

float clamp01(float value)
{
	return clamp(value, 0.000f, 1.0f);
}

int jobsCompleted = 0;

void kernel(	const unsigned int& x, 
				const unsigned int& y, 
				const unsigned int& width, 
				const unsigned int& height, 
				Color& outputColor )
{
	float aspectRatio = (float)width / height;
	Vec2 uv = Vec2(float(x) / width, float(y) / height) * 2.0f - 1.0f;
	uv.X() *= aspectRatio;

	if (abs(uv.X()) < 0.0000f)
	{
		uv.X() = 0.0001f;
	}

	float l = uv.Magnitude();

	float t = pow(abs(1.0f / (uv.X() * 50.0)), 0.5);
	t = clamp01(t);
	outputColor.SetValues(t * 2.0f, t * 4.0f, t * 8.0f, 1.0f);
	Color::Clamp(outputColor, 0.0f, 1.0f);
}

void Scene_Thread(int startingX, int startingY, int endingX, int endingY, int width, int height, int bytesPerPixel, float* pixels)
{
	Color outputColor;
	for (int y = startingY; y < endingY; ++y)
	{
		for (int x = startingX; x < endingX;  ++x)
		{
			kernel(x, y, width, height, outputColor);

			int redIndex = (y*width*bytesPerPixel) + (x*bytesPerPixel + 0);
			memcpy(&pixels[redIndex], outputColor.GetValues(), sizeof(float) * 3.0f);
		}
	}

	++jobsCompleted;
}

void Scene_Threads(int width, int height, int bytesPerPixel, float* pixels)
{

	int d = width / 5;

	std::thread t1(Scene_Thread, 0, 0, d, height, width, height, bytesPerPixel, pixels);
	t1.detach();

	std::thread t2(Scene_Thread, d, 0, d*2, height, width, height, bytesPerPixel, pixels);
	t2.detach();

	std::thread t3(Scene_Thread, d*2, 0, d*3, height, width, height, bytesPerPixel, pixels);
	t3.detach();

	std::thread t4(Scene_Thread, d * 3, 0, d * 4, height, width, height, bytesPerPixel, pixels);
	t4.detach();

	std::thread t5(Scene_Thread, d * 4, 0, width, height, width, height, bytesPerPixel, pixels);
	t5.detach();

	while (jobsCompleted < 5);
}

void Scene_NoThreads(int width, int height, int bytesPerPixel, float* pixels)
{
	float aspectRatio = (float)width / height;

	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			int redIndex	= (y*width*bytesPerPixel) + (x*bytesPerPixel + 0);
			int greenIndex	= (y*width*bytesPerPixel) + (x*bytesPerPixel + 1);
			int blueIndex	= (y*width*bytesPerPixel) + (x*bytesPerPixel + 2);

			float uvx = (float(x) / width) * 2.0f - 1.0f;
			float uvy = (float(y) / height) * 2.0f - 1.0f;
			uvx *= aspectRatio;

			if( abs(uvx) < 0.0000f )
			{
				uvx = 0.0001f;
			}

			float l = sqrt(uvx*uvx + uvy*uvy);

			float t = pow(abs( 1.0f / (l * 50.0)), 0.5);
			t = clamp01(t);

			pixels[redIndex]	= clamp01(t * 2.0f);
			pixels[greenIndex]	= clamp01(t * 4.0f);
			pixels[blueIndex]	= clamp01(t * 8.0f);
		}
	}
}

int main(int argc, char* argv)
{
	cout << "-- Ray Tracer Begin\n";

	const int width = 320;
	const int height = 240;
	const int bytesPerPixel = 3;
	float pixels[width * height * bytesPerPixel];
	
	StopWatch timer;
	timer.Start();
	Scene_Threads(width, height, bytesPerPixel, pixels);
	float elapsedTimeInMS = timer.Stop();

	PPMExporter::Export( "test2.ppm", width, height, bytesPerPixel, pixels);

	cout << "-- Ray Tracer End \n";
	cout << "STATS\n";
	cout << "Render Time: " << elapsedTimeInMS << " ms\n";
	cout << "FPS: " << 1000.0f / elapsedTimeInMS << "\n";

	return 0;
}