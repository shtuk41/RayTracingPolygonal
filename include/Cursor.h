#ifndef _CURSOR_H
#define _CURSOR_H

class Cursor
{
public:
	Cursor():x(0),y(0) {}

	float X() const { return x; }
	float Y() const { return y; }

	void Set(float _x, float _y) { x = _x; y = _y;}
	void SetX(float _x) { x = _x; }
	void SetY(float _y) { y = _y; }
	void operator=(float *arr) {x = arr[0]; y = arr[1];}

	void Set(double _x, double _y) { x = static_cast<float>(_x); y = static_cast<float>(_y);}
	void SetX(double _x) { x = static_cast<float>(_x); }
	void SetY(double _y) { y = static_cast<float>(_y); }
	void operator=(double *arr) {x = static_cast<float>(arr[0]); y = static_cast<float>(arr[1]);}

private:

	float x;
	float y;

};

#endif
