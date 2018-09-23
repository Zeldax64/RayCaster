#include <iostream>

#include <math.h>

#include "util/math/Vertex3f.h"
#include "util/math/TMatrix.h"
#include "util/objects/meshes/TCube.h"

int main() {
	// Testing transformations on TCube object
	TCube cube;
	float theta = 90.0;

	TMatrix rotatey;
	rotatey.rotateY(90.0);
	TMatrix scale;
	scale.scale(2.0, 2.0, 2.0);

	/*
	std::cout << "Printing Cube:\n";
	cube.print();
	std::cout << "Applying transformation:\n";
	cube.applyTransform(rotatey);
	cube.print();
	*/

	Vertex3f v1(1, 0, 0);
	std::cout << "Printing Vertex:\n";
	v1.print();
	v1.applyTransform(rotatey);
	std::cout << "Applying transformation:\n";
	v1.print();

	return 0;
}
