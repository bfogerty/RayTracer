import threading;
import math;
from Color import *;
import filter as f;

def RenderImage(x, y, width, height, bytesPerPixel):
	u = (float(x) / width) * 2.0 - 1.0;
	v = (float(y) / height) * 2.0 - 1.0;

	if u <= 0.00000:
		if u > -0.00001:
			u = 0.00001;

	if v <= 0.00000:
		if v > -0.00001:
			v = 0.00001;

	offset = math.sin(v * 10.0)*0.1;
	t = 1.0 / abs((u + offset) * 100.0);
	color = Color.CreateFromScalar(t);
	weights = Color.Create(8.0, 4.0, 2.0, 1.0);
	outputColor = color * weights;

	return outputColor;

def RenderJob(pixels, startX, startY, endX, endY, imageWidth, imageHeight, bytesPerPixel):
	for y in range(int(startY), int(endY)):
		for x in range(int(startX), int(endX)):
			rIndex = (y*imageWidth*bytesPerPixel) + (x*bytesPerPixel + 0);
			gIndex = (y*imageWidth*bytesPerPixel) + (x*bytesPerPixel + 1);
			bIndex = (y*imageWidth*bytesPerPixel) + (x*bytesPerPixel + 2);
			aIndex = (y*imageWidth*bytesPerPixel) + (x*bytesPerPixel + 3);

			outputColor = RenderImage(x, y, imageWidth, imageHeight, bytesPerPixel);

			pixels[rIndex] = outputColor.GetValues()[0];
			pixels[gIndex] = outputColor.GetValues()[1];
			pixels[bIndex] = outputColor.GetValues()[2];
			pixels[aIndex] = outputColor.GetValues()[3];

def Render(pixels, width, height, bytesPerPixel):

	cpuCoreCount = 1;

	jobs = [];
	for i in range(cpuCoreCount):
		startX = (i / cpuCoreCount) * width;
		endX = ((i+1) / cpuCoreCount) * width;
		t = threading.Thread(target = RenderJob, args=(pixels, startX, 0, endX, height, width, height, bytesPerPixel));
		jobs.append(t);
		t.start(); 

	for job in jobs:
		job.join();

	return pixels;
