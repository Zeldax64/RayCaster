/*
	What next? List of TODOs
	TODO: Implement shadows!
*/

#include <iostream>

#include <math.h>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/objects/meshes/MCube.h"
#include "core/objects/meshes/MTriangle.h"
#include "core/objects/geometric/GSphere.h"
#include "core/scenery/Scenery.h"
#include "core/renderer/RayCasting.h"
#include "core/light/Light.h"
#include "util/util.h"
#include "util/background.h"
#include "app/objects/SnowMan.h"

#define X_WIDTH 500
#define Y_WIDTH 500

using namespace std;

void buildScenery(Scenery * scn) {
	// Add plane
	float plane_height = -18.0;
	TMatrix scale;
	scale.scale(15.0, 0.01, 15.0);
	TMatrix rotatey, rotatez;
	rotatez.rotateZ(0.0);
	rotatey.rotateY(0.0);
	TMatrix translate1;
	translate1.translate(-0.5, -0.51, -0.5);
	TMatrix translate2;
	translate2.translate(0.0, plane_height, 0.0);
	TMatrix transf2 = translate2*rotatez*rotatey*scale*translate1;

	(scale*translate1).print();
	MCube* plane = new MCube();
	plane->applyTransform(transf2);
	plane->print();
	scn->addObj(plane);
	/*
	MTriangle* triangle = new MTriangle();
	triangle->print();
	triangle->applyTransform(rotate);
	scn->addObj(triangle);
	triangle->print();
	*/
	// Adding Snowmen
	SnowMan* snowman1 = new SnowMan(-0.0, 3.0 + plane_height, 0.0);
	SnowMan* snowman2 = new SnowMan(8.0, 3.0 + plane_height, 8.0);
	scn->addObj(snowman1);
	//scn->addObj(snowman2);

	// Adding light
	Light* light_src = new Light();
	light_src->setPosition(10.0, 10.0, 10.0);
	light_src->setAmbIntensity(0.7, 0.7, 0.7);
	light_src->setSourceIntensity(1.0, 1.0, 1.0);
	scn->addLight(light_src);
}

void buildCam(Vertex3f & pos, Vertex3f & look_at, Vertex3f & avup, float fov, Scenery * scn) {
	scn->setCamPos(pos);
	scn->setCamLookAt(look_at);
	scn->setCamAViewUp(avup);
	Camera* cam = scn->getCam();
	cam->setFOV(90.0);
	scn->calcCamCoord();
}

void renderScene(RayCasting & render) {
	Scenery* scn = render.getScenery();
	render.render();
}

int main(int argc, char **argv) {
	// Build scenery
	Scenery scn;
	buildScenery(&scn);

	// Build camera
	Vertex3f cam_pos(40.0, 8.0, 0.0);
	Vertex3f look_at(0.0, 0.0, 0.0);
	Vertex3f avup(0.0, 1.0, 0.0);
	float fov = 90.0;

	buildCam(cam_pos, look_at, avup, fov, &scn);

	// Render Debug
/*
	scn.worldToCamTransform();
	Vertex3f ray = Vertex3f(0.0,0.2, -1.0);
	Material* mat;
	Vertex3f n;
	hitObjectList(scn.objs, ray, mat, n);
	std::cout << "&mat = " << mat << "\n";
	mat->print();
	n.print();
	*/
	RayCasting render(X_WIDTH, Y_WIDTH);
	render.setScenery(&scn);

	if(argc >= 1) {
		render.loadBG(argv[1]);
	}
	renderScene(render); // Render scene

	Color* buff = render.getBuffer(); // Get buffer
	mainGL(argc, argv, render);
}
