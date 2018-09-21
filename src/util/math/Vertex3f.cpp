#include "Vertex3f.h"


Vertex3f::Vertex3f() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vertex3f::Vertex3f(float new_x, float new_y, float new_z) {
	x = new_x;
	y = new_y;
	z = new_z;
}


Vertex3f::~Vertex3f() {}

void Vertex3f::moveTo(float new_x, float new_y, float new_z) {
	x = new_x;
	y = new_y;
	z = new_z;
}

Vertex3f Vertex3f::operator+(const Vertex3f & param) {
	Vertex3f temp;
	temp.x = x + param.x;
	temp.y = y + param.y;
	temp.z = z + param.z;
	return temp;
}

Vertex3f Vertex3f::operator-(const Vertex3f & param)
{
	Vertex3f temp;
	temp.x = x - param.x;
	temp.y = y - param.y;
	temp.z = z - param.z;
	return temp;
}

Vertex3f Vertex3f::operator*(const Vertex3f & param)
{
	Vertex3f temp;
	temp.x = x * param.x;
	temp.y = y * param.y;
	temp.z = z * param.z;
	return temp;
}

float Vertex3f::norm()
{
	return sqrt(x*x + y*y + z*z);
}
