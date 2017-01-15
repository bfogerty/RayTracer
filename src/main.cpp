#include <iostream>
#include <math.h>
#include <algorithm>
#include <thread>
#include "renderer/renderer.h"
#include "math/CommonMath.h"
#include "math/vec2.h"
#include "color/color.h"
#include "time/StopWatch.h"
#include "export/PPMExporter.h"
using namespace std;

void kernel(	const unsigned int& x, 
				const unsigned int& y, 
				const unsigned int& width, 
				const unsigned int& height, 
				Color& outputColor )
{
	static float aspectRatio = (float)width / height;
	Vec2 uv = Vec2(float(x) / width, float(y) / height) * 2.0f - 1.0f;
	uv.X() *= aspectRatio;

	float t = float(pow(abs(1.0f / (((uv.X() * 300.0) + sin(uv.Y() * 5.0f)*50.0f))), 0.75f));
	t = clamp01(t);
	outputColor.SetValues(t * 2.0f, t * 4.0f, t * 8.0f, 1.0f);
	Color::Clamp(outputColor, 0.0f, 1.0f);
}

int main(int argc, char* argv)
{
	cout << "-- Ray Tracer Begin\n";

	const int width = 320;
	const int height = 240;
	const int bytesPerPixel = 3;
	
	Renderer renderer(kernel, width, height, bytesPerPixel);

	StopWatch timer;
	timer.Start();
	renderer.Render();
	float elapsedTimeInMS = timer.Stop();

	PPMExporter::Export( "test2.ppm", width, height, bytesPerPixel, renderer.GetPixels());

	cout << "-- Ray Tracer End \n";
	cout << "STATS\n";
	cout << "Render Time: " << elapsedTimeInMS << " ms\n";
	cout << "FPS: " << 1000.0f / elapsedTimeInMS << "\n";

	ShellExecute(NULL, "open", "test2.ppm", NULL, NULL, SW_SHOW);

	return 0;
}