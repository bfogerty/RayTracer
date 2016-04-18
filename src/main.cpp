#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <ctime>
using namespace std;

void WriteImageFile(int width, int height, int bytesPerPixel, const float* pixels)
{
	ofstream fileOut("test.ppm", std::ofstream::out);

	//int maxValue = 255;

	fileOut << "P3\n";
	fileOut << width << " " << height << "\n";
	fileOut << "255\n";
	fileOut << "\n";

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int redIndex	= (y*width*bytesPerPixel) + (x*bytesPerPixel + 0);
			int greenIndex	= (y*width*bytesPerPixel) + (x*bytesPerPixel + 1);
			int blueIndex	= (y*width*bytesPerPixel) + (x*bytesPerPixel + 2);

			int red		= round(pixels[redIndex]	* 255);
			int green	= round(pixels[greenIndex]	* 255);
			int blue	= round(pixels[blueIndex]	* 255);

			fileOut << red << " " << green << " " << blue << " ";
		}

		fileOut << "\n";
	}

	fileOut.close();
}

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

			if( fabs(uvx) < 0.0000f )
			{
				uvx = 0.0001f;
			}

			float l = sqrt(uvx*uvx + uvy*uvy);

			float t = pow(fabs( 1.0f / (l * 50.0)), 0.5);
			t = clamp01(t);

			pixels[redIndex]	= clamp01(t * 2.0f);
			pixels[greenIndex]	= clamp01(t * 4.0f);
			pixels[blueIndex]	= clamp01(t * 8.0f);
		}
	}
}

int main(int argc, char* argv[])
{
	cout << "-- Ray Tracer Begin\n";

	const int width = 320;
	const int height = 240;
	const int bytesPerPixel = 3;
	float pixels[width * height * bytesPerPixel];
	
	clock_t startTime = clock();
	Scene_NoThreads(width, height, bytesPerPixel, pixels);
	double elapsedTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;

	WriteImageFile(width, height, bytesPerPixel, pixels);

	cout << "-- Ray Tracer End " << elapsedTime << " secs\n";

	return 0;
}