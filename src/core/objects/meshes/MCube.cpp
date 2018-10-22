#include "core/objects/meshes/MCube.h"

MCube::MCube() {
	vertices[0].moveTo(0, 0, 0);
	vertices[1].moveTo(0, 0, 1);
	vertices[2].moveTo(1, 0, 1);
	vertices[3].moveTo(1, 0, 0);
	vertices[4].moveTo(0, 1, 0);
	vertices[5].moveTo(0, 1, 1);
	vertices[6].moveTo(1, 1, 1);
	vertices[7].moveTo(1, 1, 0);

	edges[0].setEdge(0, 1);
	edges[1].setEdge(0, 3);
	edges[2].setEdge(2, 3);
	edges[3].setEdge(1, 2);
	edges[4].setEdge(4, 5);
	edges[5].setEdge(5, 6);
	edges[6].setEdge(6, 7);
	edges[7].setEdge(4, 7);
	edges[8].setEdge(0, 5);
	edges[9].setEdge(1, 5);
	edges[10].setEdge(2, 6);
	edges[11].setEdge(3, 7);
	edges[12].setEdge(0, 2);
	edges[13].setEdge(4, 6);
	edges[14].setEdge(1, 6);
	edges[15].setEdge(2, 7);
	edges[16].setEdge(3, 4);
	edges[17].setEdge(0, 5);

	faces[0].setFace(0, 2, 1);
	faces[1].setFace(0, 3, 2);
	faces[2].setFace(4, 5, 6);
	faces[3].setFace(4, 6, 7);
	faces[4].setFace(1, 6, 5);
	faces[5].setFace(1, 2, 6);
	faces[6].setFace(2, 7, 6);
	faces[7].setFace(2, 3, 7);
	faces[8].setFace(0, 4, 3);
	faces[9].setFace(3, 4, 7);
	faces[10].setFace(0, 5, 4);
	faces[11].setFace(0, 1, 5);

	this->material.setAmb(0.0, 1.0, 0.0);
  this->material.setDif(0.3, 0.3, 0.3);
  this->material.setSpe(0.2, 0.2, 0.2);
}

MCube::MCube(Material & mat) {
	vertices[0].moveTo(0, 0, 0);
	vertices[1].moveTo(0, 0, 1);
	vertices[2].moveTo(1, 0, 1);
	vertices[3].moveTo(1, 0, 0);
	vertices[4].moveTo(0, 1, 0);
	vertices[5].moveTo(0, 1, 1);
	vertices[6].moveTo(1, 1, 1);
	vertices[7].moveTo(1, 1, 0);

	edges[0].setEdge(0, 1);
	edges[1].setEdge(0, 3);
	edges[2].setEdge(2, 3);
	edges[3].setEdge(1, 2);
	edges[4].setEdge(4, 5);
	edges[5].setEdge(5, 6);
	edges[6].setEdge(6, 7);
	edges[7].setEdge(4, 7);
	edges[8].setEdge(0, 5);
	edges[9].setEdge(1, 5);
	edges[10].setEdge(2, 6);
	edges[11].setEdge(3, 7);
	edges[12].setEdge(0, 2);
	edges[13].setEdge(4, 6);
	edges[14].setEdge(1, 6);
	edges[15].setEdge(2, 7);
	edges[16].setEdge(3, 4);
	edges[17].setEdge(0, 5);

	faces[0].setFace(0, 2, 1);
	faces[1].setFace(0, 3, 2);
	faces[2].setFace(4, 5, 6);
	faces[3].setFace(4, 6, 7);
	faces[4].setFace(1, 6, 5);
	faces[5].setFace(1, 2, 6);
	faces[6].setFace(2, 7, 6);
	faces[7].setFace(2, 3, 7);
	faces[8].setFace(0, 4, 3);
	faces[9].setFace(3, 4, 7);
	faces[10].setFace(0, 5, 4);
	faces[11].setFace(0, 1, 5);

	material = mat;
}

MCube::~MCube() {
}

void MCube::applyTransform(const TMatrix & param) {
	for(uint8_t i = 0; i < 8; i++){
		vertices[i].applyTransform(param);
	}
}

// TODO: This method will produce a full red square
// TODO: There might be some bugs in this function. Gotta find them
float MCube::hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat) {
	float best_t = FLT_MAX;
	for (int i = 0; i < 12; i++) {
		Face3f face = faces[i];
		Vertex3f v0 = vertices[face.vertices[0]];
		Vertex3f v1 = vertices[face.vertices[1]];
		Vertex3f v2 = vertices[face.vertices[2]];

		Vertex3f n;

		float tint = hitTriangle(ray, v0, v1, v2, n);

		if (tint >= 1.0 && tint < best_t) {
			best_t = tint;
			ret_mat = &this->material;
			ret_n = n;
		}
	}
	return best_t;
}

Material* MCube::getMaterial() { return &this->material; }

void MCube::print(){

	for(uint8_t i = 0; i < 8; i++){
		vertices[i].print();
	}

	/*
	std::cout << "Normals:\n";

	for(int i = 0; i < 12; i++){
		std::cout << "--- Face " << i <<" ---\n";
		Face3f face = faces[i];

		Vertex3f v0 = vertices[face.vertices[0]];
		Vertex3f v1 = vertices[face.vertices[1]];
		Vertex3f v2 = vertices[face.vertices[2]];
		std::cout << "v0: ";
		v0.print();
		std::cout << "v1: ";v1.print();
		std::cout << "v2: ";v2.print();

		Vertex3f u = v1 - v0;
		Vertex3f v = v2 - v0;

		std::cout << "u: ";u.print();
		std::cout << "v: ";v.print();
		Vertex3f n = (u.crossProduct(v)).unit();
		std::cout << "n: ";n.print();
		std::cout << "\n ";
	}
	*/
}
