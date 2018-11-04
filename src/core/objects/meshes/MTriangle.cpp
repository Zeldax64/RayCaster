#include "core/objects/meshes/MTriangle.h"

MTriangle::MTriangle() {
  vertices[0].moveTo(0, 0, 0);
	vertices[1].moveTo(0, 1,-1);
	vertices[2].moveTo(0, 1, 0);

  edges[0].setEdge(0, 1);
	edges[1].setEdge(0, 2);
	edges[2].setEdge(1, 2);

  faces[0].setFace(0, 1, 2);

  this->material.setAmb(1.0, 0.0, 0.0);
  this->material.setDif(0.3, 0.3, 0.3);
  this->material.setSpe(0.2, 0.2, 0.2, 1.0);
}

MTriangle::MTriangle(Material & mat) {
  vertices[0].moveTo(0, 0, 0);
	vertices[1].moveTo(0, 1,-1);
	vertices[2].moveTo(0, 1, 0);

  edges[0].setEdge(0, 1);
	edges[1].setEdge(0, 2);
	edges[2].setEdge(1, 2);

  faces[0].setFace(0, 1, 2);

  this->material = mat;
}

MTriangle::~MTriangle() { }

void MTriangle::applyTransform(const TMatrix & param) {
	for(uint8_t i = 0; i < 3; i++){
		vertices[i].applyTransform(param);
	}
}

float MTriangle::hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat) {
	Face3f face = faces[0];
	Vertex3f v0 = vertices[face.vertices[0]];
	Vertex3f v1 = vertices[face.vertices[1]];
	Vertex3f v2 = vertices[face.vertices[2]];

  Vertex3f n;

  float tint = hitTriangle(ray, v0, v1, v2, n);

	// TODO: improve hit checking to allow diferences between hidden faces
	if (tint >= 1.0) {
		ret_mat = &this->material;
    ret_n = n;
	}
	return tint;
}

Material* MTriangle::getMaterial() { return &this->material; }

void MTriangle::print(){
	for(uint8_t i = 0; i < 3; i++){
		vertices[i].print();
	}
}
