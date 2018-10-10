

#include "core/math/Vertex3f.h"
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
	setX(new_x);
	setY(new_y);
	setZ(new_z);
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

Vertex3f Vertex3f::operator - () const{
	Vertex3f temp;
	temp.x = -x;
	temp.y = -y;
	temp.z = -z;
	return temp;
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

Vertex3f Vertex3f::operator * (const float & param) {
	Vertex3f temp;
	temp.x = x * param;
	temp.y = y * param;
	temp.z = z * param;
	return temp;
}

Vertex3f Vertex3f::operator*(const Vertex3f & param) {
	Vertex3f temp;
	temp.x = x * param.x;
	temp.y = y * param.y;
	temp.z = z * param.z;
	return temp;
}

Vertex3f Vertex3f::operator / (const float & param) {
	Vertex3f temp(
		this->getX() / param,
		this->getY() / param,
		this->getZ() / param
	);

	return temp;

}
void Vertex3f::operator = (const Vertex3f & param) {
	this->x = param.x;
	this->y = param.y;
	this->z = param.z;
}


// TODO: implement
float Vertex3f::dotProduct(const Vertex3f &param) {
	return getX() * param.x +
				 getY() * param.y +
				 getZ() * param.z;
}

Vertex3f Vertex3f::crossProduct(const Vertex3f &param) {
	Vertex3f temp(
		y * param.z - z * param.y,
		z * param.x - x * param.z,
		x * param.y - y * param.x
	);

	return temp;
}

float Vertex3f::length() {
	return sqrt(x*x + y*y + z*z);
}

Vertex3f Vertex3f::unit(){
	float length = this->length();
	return Vertex3f(x/length, y/length, z/length);
}

void Vertex3f::setX(float x) { this->x = x; }
void Vertex3f::setY(float y) { this->y = y; }
void Vertex3f::setZ(float z) { this->z = z; }

float Vertex3f::getX() { return this->x; }
float Vertex3f::getY() { return this->y; }
float Vertex3f::getZ() { return this->z; }

void Vertex3f::print() {
	std::cout << "[" << x << "]";
	std::cout << "[" << y << "]";
	std::cout << "[" << z << "]\n";
}
