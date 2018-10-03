/*
	What next? List of TODO!
	1) Finish implementation of worldBasisToCoord TMatrix.cpp; OK
	2) Create a Buffer/Color/Window class; Color Ok
	3) Do render; - Under Debug
			- Ray generation; Ok
			- Hit object system; Ok
			- Return a result (any color); Ok

	4) Check results using an API to paint a screen;
*/

#include <iostream>

#include <math.h>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/objects/meshes/MCube.h"
#include "core/objects/geometric/GSphere.h"
#include "core/scenery/Scenery.h"
#include "core/renderer/RayCasting.h"
#include "util/util.h"

#define X_WIDTH 300
#define Y_WIDTH 300

using namespace std;

void buildScenery(Scenery * scn) {
	/*
	MCube* cube = new MCube();
	TMatrix scale;
	scale.scale(3.0, 3.0, 3.0);
	cube->applyTransform(scale);
	scn->addObj(cube);
	*/
	GSphere* sphere = new GSphere(Vertex3f(0.0, 0.0, 0.0), 5.0);
	scn->addObj(sphere);
}

void buildCam(Vertex3f & pos, Vertex3f & look_at, Vertex3f & avup, Scenery * scn) {
	scn->setCamPos(pos);
	scn->setCamLookAt(look_at);
	scn->setCamAViewUp(avup);
	scn->calcCamCoord();
}

void renderScene(RayCasting & render) {
	Scenery* scn = render.getScenery();
	//scn->getObj(0)->print();
	scn->worldToCamTransform();
	scn->getObj(0)->print();
	render.render();

}

int main(int argc, char **argv) {
	// Build scenery
	Scenery scn;
	buildScenery(&scn);
	// Build camera
	Vertex3f cam_pos(5.0, 0.0, 0.0);
	Vertex3f look_at(0.0, 0.0, 0.0);
	Vertex3f avup(0.0, 0.0, 1.0);
	buildCam(cam_pos, look_at, avup, &scn);

	// Render
	RayCasting render(X_WIDTH, Y_WIDTH);
	render.setScenery(&scn);
	renderScene(render); // Render scene

	Color* buff = render.getBuffer(); // Get buffer

	mainGL(argc, argv, X_WIDTH, Y_WIDTH, buff);
}
