'''void kernel(	const unsigned int& x, 
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
}'''

import math;

def clamp01(x):
	if x <= 0.001:
		return 0.001;

	if x >= 1.0:
		return 1.0;

	return x;

def DoFilter(x, y, width, height):
	aspectRatio = float(width) / float(height);
	u = (float(x) / width) * 2.0 - 1.0;
	v = (float(y) / height) * 2.0 - 1.0;

	u = u * aspectRatio;

	d = abs(v * 300.0);
	if d <= 0.001:
		d = 0.001

	t = float(1.0 / d);

	if t < 0.0:
		t = 0.0;

	if t > 1.0:
		t = 1.0;

	t = clamp01(t);

	r = clamp01(t*8.0);
	g = clamp01(t*4.0);
	b = clamp01(t*2.0);

	return (r,g,b, 1.0);