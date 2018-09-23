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

void Vertex3f::applyTransform(const TMatrix & param) {
	float xtemp, ytemp, ztemp;

	xtemp = x * param.matrix[0][0] +
					y * param.matrix[0][1] +
					z * param.matrix[0][2] +
							param.matrix[0][3];

	ytemp = x * param.matrix[1][0] +
					y * param.matrix[1][1] +
					z * param.matrix[1][2] +
							param.matrix[1][3];

	ztemp = x * param.matrix[2][0] +
					y * param.matrix[2][1] +
					z * param.matrix[2][2] +
							param.matrix[2][3];

	moveTo(xtemp, ytemp, ztemp);
}

Vertex3f Vertex3f::operator+(const Vertex3f & param) {
	Vertex3f temp;
	temp.x = x + param.x;
	temp.y = y + param.y;
	temp.z = z + param.z;
	return temp;
}

Vertex3f Vertex3f::operator-(const Vertex3f & param) {
	Vertex3f temp;
	temp.x = x - param.x;
	temp.y = y - param.y;
	temp.z = z - param.z;
	return temp;
}

Vertex3f Vertex3f::operator*(const Vertex3f & param) {
	Vertex3f temp;
	temp.x = x * param.x;
	temp.y = y * param.y;
	temp.z = z * param.z;
	return temp;
}

// TODO: implement
float Vertex3f::scalarProduct(const Vertex3f &param) {

}

Vertex3f Vertex3f::crossProduct(const Vertex3f &param) {
	Vertex3f temp(
		y * param.z - z * param.y,
		z * param.x - x * param.z,
		x * param.y - y * param.x
	);

	return temp;
}

float Vertex3f::norm() {
	return sqrt(x*x + y*y + z*z);
}

void Vertex3f::print() {
	std::cout << "[" << x << "]";
	std::cout << "[" << y << "]";
	std::cout << "[" << z << "]\n";
}
