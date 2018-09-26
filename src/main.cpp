#include <iostream>

#include <math.h>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/objects/meshes/TCube.h"
#include "core/scenery/Scenery.h"
int main() {
	// Testing transformations on TCube object
	TCube* cube = new TCube();
	float theta = 90.0;
	Scenery scn;
	TMatrix rotatey;
	rotatey.rotateY(90.0);
	TMatrix scale;
	scale.scale(2.0, 2.0, 2.0);

	cube->print();
	scn.addObj(cube);
	scn.applyTransformAll(scale);
	cube->print();

/*
	Vertex3f v1(1, 0, 0);
	std::cout << "Printing Vertex:\n";
	v1.print();
	v1 = -v1;
	std::cout << "Applying transformation:\n";
	v1.print();
*/
	return 0;
}
