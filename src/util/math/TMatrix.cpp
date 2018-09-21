

#include "TMatrix.h"

void TMatrix::zeros() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = 0.0;
		}
	}
	matrix[3][3] = 1.0;
}

TMatrix::TMatrix() {
	zeros();
}


TMatrix::~TMatrix() {
}

void TMatrix::scale(float x, float y, float z) {
	zeros();
	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
}

void TMatrix::translate(float x, float y, float z) {
	zeros();
	matrix[0][3] = x;
	matrix[0][3] = y;
	matrix[0][3] = z;
}

void TMatrix::rotateX(float theta) {
	float cos_o = cos(theta);
	float sin_o = sin(theta);

	zeros();

	matrix[0][0] = 1.0;
	matrix[1][1] = cos_o; matrix[1][2] = -sin_o;
	matrix[2][1] = sin_o; matrix[2][2] = cos_o;
}

void TMatrix::rotateY(float theta) {
	float cos_o = cos(theta);
	float sin_o = sin(theta);

	zeros();

	matrix[1][1] = 1.0;
	matrix[0][0] =  cos_o; matrix[0][2] = sin_o;
	matrix[2][0] = -sin_o; matrix[2][2] = cos_o;
}

void TMatrix::rotateZ(float theta) {
	float cos_o = cos(theta);
	float sin_o = sin(theta);

	zeros();

	matrix[2][2] = 1.0;
	matrix[0][0] = cos_o; matrix[0][1] = -sin_o;
	matrix[0][1] = sin_o; matrix[1][1] = cos_o;
}

void TMatrix::print() {
	for (int i = 0; i < 3; i++) {
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
