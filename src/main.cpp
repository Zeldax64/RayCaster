/*
	What next? List of TODOs!
	TODO: Check TODO in Scenery.cpp hitRay
	TODO: Implement hit object to model SnowMan
	Special TODO: fix triangle intersect from MCube and MTriangle
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
	// Snowman Debug
	/*
	TMatrix scale;
	scale.scale(1.0, 1.0, 1.0);
	TMatrix rotate;
	rotate.rotateY(-5.0);
	TMatrix translate;
	translate.translate(0.0, 0.0, 0.0);
	*/
	/*
	MCube* cube = new MCube();
	cube->applyTransform(scale);
	scn->addObj(cube);
	*/
	/*
	MTriangle* triangle = new MTriangle();
	triangle->applyTransform(translate*scale);
	scn->addObj(triangle);
	triangle->print();
	*/
	// Adding Snowmen
	SnowMan* snowman1 = new SnowMan(-6.0, -6.0, 3.0);
	SnowMan* snowman2 = new SnowMan(-24.0, -6.0, -3.0);

	scn->addObj(snowman1);
	scn->addObj(snowman2);

	// Adding light
	Light* light_src = new Light();
	light_src->setPosition(10.0, 10.0, 10.0);
	light_src->setAmbIntensity(1.0, 1.0, 1.0);
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
	Vertex3f cam_pos(10.0, 0.0, 0.0);
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
	mainGL(argc, argv, render.getWidth(), render.getHeight(), buff);
}
