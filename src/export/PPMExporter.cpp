#include "PPMExporter.h"
#include <fstream>
using namespace std;

void PPMExporter::Export(const char* filename, int width, int height, int bytesPerPixel, const float* pixels)
{
	ofstream fileOut(filename, std::ofstream::out);

	int maxValue = 255;

	fileOut << "P3\n";
	fileOut << width << " " << height << "\n";
	fileOut << "255\n";
	fileOut << "\n";

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int redIndex = (y*width*bytesPerPixel) + (x*bytesPerPixel + 0);
			int greenIndex = (y*width*bytesPerPixel) + (x*bytesPerPixel + 1);
			int blueIndex = (y*width*bytesPerPixel) + (x*bytesPerPixel + 2);

			int red = round(pixels[redIndex] * 255);
			int green = round(pixels[greenIndex] * 255);
			int blue = round(pixels[blueIndex] * 255);

			fileOut << red << " " << green << " " << blue << " ";
		}

		fileOut << "\n";
	}

	fileOut.close();
}