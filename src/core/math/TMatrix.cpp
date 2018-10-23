#include "core/math/TMatrix.h"

void TMatrix::identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) matrix[i][j] = 1.0;
			else matrix[i][j] = 0.0;
		}
	}
}

void TMatrix::zeros() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = 0.0;
		}
	}
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
	matrix[1][3] = y;
	matrix[2][3] = z;
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
	matrix[1][0] = sin_o; matrix[1][1] = cos_o;
}

// TODO: Incomplete! check matrix[3][x] assignments.
void TMatrix::worldBasisToCoord(Vertex3f & coord_x, Vertex3f & coord_y, Vertex3f & coord_z, Vertex3f & coord_o) {
	identity();
	matrix[0][0] = coord_x.getX();
	matrix[0][1] = coord_x.getY();
	matrix[0][2] = coord_x.getZ();

	matrix[1][0] = coord_y.getX();
	matrix[1][1] = coord_y.getY();
	matrix[1][2] = coord_y.getZ();

	matrix[2][0] = coord_z.getX();
	matrix[2][1] = coord_z.getY();
	matrix[2][2] = coord_z.getZ();

	matrix[0][3] = -coord_x.dotProduct(coord_o);
	matrix[1][3] = -coord_y.dotProduct(coord_o);
	matrix[2][3] = -coord_z.dotProduct(coord_o);
}

void TMatrix::coordBasisToWorld(Vertex3f & coord_x, Vertex3f & coord_y, Vertex3f & coord_z, Vertex3f & coord_o) {
	identity();
	matrix[0][0] = coord_x.getX();
	matrix[1][0] = coord_x.getY();
	matrix[2][0] = coord_x.getZ();

	matrix[0][1] = coord_y.getX();
	matrix[1][1] = coord_y.getY();
	matrix[2][1] = coord_y.getZ();

	matrix[0][2] = coord_z.getX();
	matrix[1][2] = coord_z.getY();
	matrix[2][2] = coord_z.getZ();

	matrix[0][3] = coord_o.getX();
	matrix[1][3] = coord_o.getY();
	matrix[2][3] = coord_o.getZ();
}


TMatrix TMatrix::operator*(const TMatrix & param) {
	TMatrix temp;
	temp.zeros();

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

void TMatrix::print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << "[" << matrix[i][j] << "] ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
