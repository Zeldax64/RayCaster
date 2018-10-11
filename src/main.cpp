/*
	TODO: Check TODO in Scenery.cpp hitRay
	TODO: Implement hit object to model SnowMan
	Special TODO: fix triangle intersect from MCube and MTriangle
	What next? List of TODOs!


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

#include "app/objects/SnowMan.h"

#define X_WIDTH 250
#define Y_WIDTH 250

using namespace std;

void buildScenery(Scenery * scn) {
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
	// Body
	GSphere* body = new GSphere(Vertex3f(0.0, 0.0, 0.0),
																3.0,
																1.0, 1.0, 1.0);

	// Head
	GSphere* head = new GSphere(Vertex3f(0.0, 4.0, 0.0),
																1.0,
																1.0, 1.0, 1.0
											);

	// Left eye
	GSphere* left_eye = new GSphere(Vertex3f(1.0, 4.25, 0.45),
																	0.15,
																	0.0, 0.0, 0.0
																);

	// Right eye
	GSphere* right_eye = new GSphere(Vertex3f(1.0, 4.25, -0.45),
																	0.15,
																	0.0, 0.0, 0.0
																	);
	// Lower button
	float theta_lower = 25.0 * M_PI / 180.0;
	GSphere* lower_button = new GSphere(Vertex3f(3.0*cos(theta_lower), 3.0*sin(theta_lower), 0.0),
																	0.3,
																	0.0, 0.0, 0.0
																	);
	float theta_upper =  40.0 * M_PI / 180.0;
	GSphere* upper_button = new GSphere(Vertex3f(3.0*cos(theta_upper), 3.0*sin(theta_upper), 0.0),
																			0.3,
																			0.0, 0.0, 0.0
																		  );
	scn->addObj(body);
	scn->addObj(head);
	scn->addObj(left_eye);
	scn->addObj(right_eye);
	scn->addObj(upper_button);
	scn->addObj(lower_button);
/*
	SnowMan* snowman = new SnowMan();
	scn->addObj(snowman);
*/
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
	//scn->getObj(0)->print();
	std::cout << scn->isCoordWorld();
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

	// Render
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
	renderScene(render); // Render scene

	Color* buff = render.getBuffer(); // Get buffer

	mainGL(argc, argv, X_WIDTH, Y_WIDTH, buff);
}
