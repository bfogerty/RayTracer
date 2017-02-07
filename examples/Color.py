class Color(object):

	def __init__(self):
		self._color = [0.0,0.0,0.0,0.0];

	def Create(r=0.0,g=0.0,b=0.0,a=1.0):
		color = Color();
		color.SetValues([r,g,b,a]);
		return color;

	def CreateFromScalar(t=0.0):
		color = Color();
		color.SetValues([t,t,t,t]);
		return color;

	def SetValues(self, colorValues):
		r = colorValues[0];
		g = colorValues[1];
		b = colorValues[2];
		a = colorValues[3];

		self._color[0] = float(r);
		self._color[1] = float(g);
		self._color[2] = float(b);
		self._color[3] = float(a);

	def FillValues(self, t):
		self._color[0] = float(t);
		self._color[1] = float(t);
		self._color[2] = float(t);
		self._color[3] = float(t);

	def GetValues(self):
		return self._color;

	def __add__(self, rhs):
		r = self._color[0] + rhs._color[0];
		g = self._color[1] + rhs._color[1];
		b = self._color[2] + rhs._color[2];
		a = self._color[3] + rhs._color[3];

		result = Color();
		result.SetValues([r,g,b,a]);

		return result;

	def __sub__(self, rhs):
		r = self._color[0] - rhs._color[0];
		g = self._color[1] - rhs._color[1];
		b = self._color[2] - rhs._color[2];
		a = self._color[3] - rhs._color[3];

		result = Color();
		result.SetValues([r,g,b,a]);

		return result;

	def __mul__(self, rhs):
		r = self._color[0] * rhs._color[0];
		g = self._color[1] * rhs._color[1];
		b = self._color[2] * rhs._color[2];
		a = self._color[3] * rhs._color[3];

		result = Color();
		result.SetValues([r,g,b,a]);

		return result;

	def __rmul__(self, rhs):
		r = self._color[0] * rhs._color[0];
		g = self._color[1] * rhs._color[1];
		b = self._color[2] * rhs._color[2];
		a = self._color[3] * rhs._color[3];

		result = Color();
		result.SetValues([r,g,b,a]);

		return result;

	def Clamp(color, minValue, maxValue):

		r = color[0];
		g = color[1];
		b = color[2];
		a = color[3];

		if r < minValue: r = minValue;
		if r > maxValue: r = maxValue;

		if g < minValue: g = minValue;
		if g > maxValue: g = maxValue;

		if b < minValue: b = minValue;
		if b > maxValue: b = maxValue;

		if a < minValue: a = minValue;
		if a > maxValue: a = maxValue;

		return Color(r,g,b,a);

	def Lerp(startColor, endColor, t):
		oneMinusT = 1.0 - t;
		r = (oneMinusT * startColor._color[0]) + (t * endColor._color[0]);
		g = (oneMinusT * startColor._color[1]) + (t * endColor._color[1]);
		b = (oneMinusT * startColor._color[2]) + (t * endColor._color[2]);
		a = (oneMinusT * startColor._color[3]) + (t * endColor._color[3]);

		return Color(r,g,b,a);