#include "core/math/TMatrix.h"

void TMatrix::identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) matrix[i][j] = 1.0;
			else matrix[i][j] = 0.0;
		}
	}
	matrix[3][3] = 1.0;
}

float TMatrix::convertToRadians(float theta) {
	return theta * M_PI / 180.0;
}


TMatrix::TMatrix() {
	identity();
}


TMatrix::~TMatrix() {
}

void TMatrix::scale(float x, float y, float z) {
	identity();
	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
}

void TMatrix::translate(float x, float y, float z) {
	identity();
	matrix[0][3] = x;
	matrix[0][3] = y;
	matrix[0][3] = z;
}

void TMatrix::rotateX(float theta) {
	theta = convertToRadians(theta);
	float cos_o = cos(theta);
	float sin_o = sin(theta);

	identity();

	matrix[0][0] = 1.0;
	matrix[1][1] = cos_o; matrix[1][2] = -sin_o;
	matrix[2][1] = sin_o; matrix[2][2] = cos_o;
}

void TMatrix::rotateY(float theta) {
	theta = convertToRadians(theta);
	float cos_o = cos(theta);
	float sin_o = sin(theta);

	identity();

	matrix[1][1] = 1.0;
	matrix[0][0] =  cos_o; matrix[0][2] = sin_o;
	matrix[2][0] = -sin_o; matrix[2][2] = cos_o;
}

void TMatrix::rotateZ(float theta) {
	theta = convertToRadians(theta);
	float cos_o = cos(theta);
	float sin_o = sin(theta);

	identity();

	matrix[2][2] = 1.0;
	matrix[0][0] = cos_o; matrix[0][1] = -sin_o;
	matrix[0][1] = sin_o; matrix[1][1] = cos_o;
}
/*
void TMatrix::coordTransform(const Vertex3f & x, const Vertex3f & y, const Vertex3f & z, const Vertex3f & e) {
	matrix[0][0] = x.x;
	matrix[1][0] = x.y;
	matrix[2][0] = x.z;

	matrix[0][1] = y.x;
	matrix[1][1] = y.y;
	matrix[2][1] = y.z;

	matrix[0][2] = z.x;
	matrix[1][2] = z.y;
	matrix[2][2] = z.z;

	matrix[0][3] = e.x;
	matrix[1][3] = e.y;
	matrix[2][3] = e.z;
}
*/

void TMatrix::print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << "[" << matrix[i][j] << "] ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

TMatrix TMatrix::operator*(const TMatrix & param)
{
	TMatrix temp;
	int row;
	int col;
	for (row = 0; row < 4; row++) {
		for (col = 0; col < 4; col++) {
			for (int inner = 0; inner < 4; inner++) {
				temp.matrix[row][col] += matrix[row][inner] * param.matrix[inner][col];
			}
		}
	}

	return temp;
}
