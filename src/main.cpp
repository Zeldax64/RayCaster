/*
	What next? List of TODO!
	1) Finish implementation of worldBasisToCoord TMatrix.cpp;
	2) Create a Buffer/Color/Window class;
	3) Do render;
			- Ray generation;
			- Hit object system;
			- Return a result (any color);
	4) Check results using an API to paint a screen;
*/

#include <iostream>

#include <math.h>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/objects/meshes/TCube.h"
#include "core/scenery/Scenery.h"

void buildScenery(Scenery * scn) {
	TCube* cube = new TCube();

	scn->addObj(cube);

}

void buildCam(Vertex3f & pos, Vertex3f & look_at, Vertex3f & avup, Scenery * scn) {
	scn->setCamPos(pos);
	scn->setCamLookAt(look_at);
	scn->setCamAViewUp(avup);
	scn->calcCamCoord();
}

void render();

int main() {
	// Testing transformations on TCube object
	Scenery scn;
	buildScenery(&scn);
	Vertex3f cam_pos(5.0, 5.0, 5.0);
	Vertex3f look_at(0.0, 0.0, 0.0);
	Vertex3f avup(0.0, 0.0, 1.0);
	buildCam(cam_pos, look_at, avup, &scn);

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
