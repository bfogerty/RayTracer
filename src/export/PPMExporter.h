#ifndef __PPMEXPORTER__
#define __PPMEXPORTER__

class PPMExporter
{
public:
	static void Export(const char* filename, int width, int height, int bytesPerPixel, const float* pixels);
};

#endif