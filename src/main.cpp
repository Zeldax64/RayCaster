/*
	What next? List of TODOs
	TODO: Implement Spotlight
	TODO: Implement back faces test
	TODO: Check intersect.cpp to optimize some functions
*/

#include <iostream>
#include <vector>

#include <math.h>

#include "core/math/Vertex3f.h"
#include "core/math/Face3f.h"
#include "core/math/TMatrix.h"
#include "core/objects/meshes/MCube.h"
#include "core/objects/meshes/MObj.h"
#include "core/objects/meshes/MTriangle.h"
#include "core/math/Ray.h"
#include "core/objects/geometric/GSphere.h"
#include "core/scenery/Scenery.h"
#include "core/renderer/RayCasting.h"
#include "core/light/Light.h"
#include "core/light/LPoint.h"

#include "util/util.h"
#include "util/background.h"
#include "util/objloader.h"

// Objects includes
#include "app/objects/SnowMan.h"
#include "app/objects/Pot.h"

#define X_WIDTH 500
#define Y_WIDTH 500

using namespace std;

void buildScenery(Scenery * scn) {
	// Add plane
	float plane_height = 0.0;
	TMatrix scale;
	scale.scale(30.0, 0.01, 30.0);
	TMatrix rotatey, rotatez;
	rotatez.rotateZ(0.0);
	rotatey.rotateY(0.0);
	TMatrix translate1;
	translate1.translate(-0.5, -0.51, -0.5);
	TMatrix translate2;
	translate2.translate(0.0, plane_height, 0.0);
	TMatrix transf2 = translate2*rotatez*rotatey*scale*translate1;

	MCube* plane = new MCube();
	plane->applyTransform(transf2);

	// Adding Snowmen
	SnowMan* snowman1 = new SnowMan(-0.0, 3.0 + plane_height, 0.0);
	SnowMan* snowman2 = new SnowMan(8.0, 3.0 + plane_height, 8.0);
	//scn->addObj(snowman1);
	//scn->addObj(snowman2);

	Material* mat = new Material(0.8, 0.0, 0.0, 0.2, 0.2, 0.2, 1.0, 0.0, 0.0, 0.0);
	MCube* cube = new MCube(*mat);
	scale.scale(4.0, 4.0, 4.0);
	translate1.translate(0.0, 0.0, 0.0);
	cube->applyTransform(translate1*scale);

	Vertex3f c; c.moveTo(0.0, 0.0, 0.0);
	GSphere* sphere = new GSphere(c, 2, *mat);

	MTriangle* tr = new MTriangle(*mat);
	rotatez.rotateZ(90.0);
	translate1.translate(0.0, 5.0, 0.0);
	tr->applyTransform(translate1*rotatez*scale);

	std::cout << "Triangle: \n";
	tr->print();

	std::cout << "Plane: \n";
	plane->print();


	Pot* pot = new Pot();
	scale.scale(10.0, 10.0, 10.0);
	pot->applyTransform(scale);


	//scn->addObj(tr);
	//scn->addObj(pot);
	//scn->addObj(cube);
	//scn->addObj(plane);
	//scn->addObj(sphere);

	// Adding light
	LPoint* light_src1 = new LPoint();
	light_src1->setPosition(40.0, 40.0, 40.0);
	light_src1->setSourceIntensity(0.7, 0.7, 0.7);
	LPoint* light_src2 = new LPoint();
	light_src2->setPosition(0.0, 25.5, 0.0);
	light_src2->setSourceIntensity(0.7, 0.7, 0.7);

	scn->addLight(light_src1);
	//scn->addLight(light_src2);
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
	render.render();
}

int main(int argc, char **argv) {
	// Build scenery
	Scenery scn;
	buildScenery(&scn);

	// Build camera
	Vertex3f cam_pos(0.0, 40.0, 0.0);
	Vertex3f avup(1.0, 0.0, 0.0);

	Vertex3f look_at(0.0, 0.0, 0.0);
	float fov = 90.0;

	buildCam(cam_pos, look_at, avup, fov, &scn);

	// Render Debug
	/*
	scn.worldToCamTransform();
	float l = 0; float c = 436;

	float dx = 1.0/X_WIDTH;
	float dy = 1.0/Y_WIDTH;
	float x = -(1.0/2) + dx/2 + c * dx;
	float y = (1.0/2) - dy/2 - l * dy;
	Vertex3f dir = Vertex3f(x, y, -1.0);
	Ray ray(dir);
	Material* mat;
	Vertex3f n;
	float t = hitObjectList(scn.objs, ray, mat, n);
	std::cout << "&mat = " << mat << "\n";
	mat->print();
	std::cout << "t = " << t << "\n";
	*/
	/*
	std::vector <Vertex3f> vertices;
	std::vector <Face3f> faces;
	bool obj = loadOBJ("cube.obj", &vertices, &faces);
	std::cout << "obj: " << obj << "\n";
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].print();
	}
	for (int i = 0; i < faces.size(); i++) {
		faces[i].print();
	}
	*/

	MObj* obj = new MObj();
	bool load = obj->loadObj("YoungLink.obj");
	if(!load) {
		return 0;
	}
	scn.addObj(obj);
	TMatrix scale, rotatex, rotatey, rotatez;
	rotatez.rotateZ(90);
	rotatex.rotateX(90);
	rotatey.rotateY(90);
	scale.scale(0.2, 0.2, 0.2);
	obj->applyTransform(scale);

	RayCasting render(X_WIDTH, Y_WIDTH);

	render.setScenery(&scn);

	if(argc >= 1) {
		render.loadBG(argv[1]);
	}

	mainGL(argc, argv, render);
}
