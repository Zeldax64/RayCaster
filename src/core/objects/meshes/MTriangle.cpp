#include "core/objects/meshes/MTriangle.h"

MTriangle::MTriangle() {
  vertices[0].moveTo(0, 0, 0);
	vertices[1].moveTo(0, 1,-1);
	vertices[2].moveTo(0, 1, 0);

  edges[0].setEdge(0, 1);
	edges[1].setEdge(0, 2);
	edges[2].setEdge(1, 2);

  faces[0].setFace(0, 1, 2);
}

MTriangle::~MTriangle() { }

void MTriangle::applyTransform(const TMatrix & param) {
	for(uint8_t i = 0; i < 3; i++){
		vertices[i].applyTransform(param);
	}
}

bool MTriangle::hitObject(Vertex3f & ray, Color & col) {
	bool found = false;

	Face3f face = faces[0];
	Vertex3f v0 = vertices[face.vertices[0]];
	Vertex3f v1 = vertices[face.vertices[1]];
	Vertex3f v2 = vertices[face.vertices[2]];

	Vertex3f u = v1 - v0;
	Vertex3f v = v2 - v0;

	Vertex3f n = (v1.crossProduct(v2)).unit();

	/* Calculate intersection point of ray and plane */
	float tint = v0.dotProduct(n) / ray.dotProduct(n);
	/*
	std::cout << "V0 = " ; v0.print();
	std::cout << "V1 = " ; v1.print();
	std::cout << "V2 = " ; v2.print();

	std::cout << "Tint = " << tint << "\n";
	*/
	//std::cin.get();
	// TODO: Check if this if is correct or not
	if (tint < 1.0) {
		//std::cout << "Tint < 0 = " << tint << "\n";
		return found;
	}
		//std::cout << "Tint = " << tint << "\n";
	Vertex3f Pi = ray * tint;
	// TODO: Possible improvement
	// If ray * n -> 0, then Pi -> infinity. A check could be done here
	// like ray . n == 0;

	/* Calculate whether the point is in the triangle */
	// Partial dot products
	Vertex3f w = Pi - v0;

	float a = u.dotProduct(v); // a = (u . v);
	float b = w.dotProduct(v); // b = (w . v);
	float c = v.dotProduct(v); // c = (v . v);
	float d = w.dotProduct(u); // d = (w . u);
	float e = u.dotProduct(u); // e = (u . u);
	float den = a * a - e * c; // Denominator

	float si = (a * b - c * d) / den;
	float ti = (a * d - e * b) / den;

	// TODO: improve hit checking to allow diferences between hidden faces
	if (si >= 0.0 && ti >= 0.0 && si+ti <= 1.0) {
		found = true;
		col.setColor(1.0, 0.0, 0.0); // Setting red
		return found;
	}
	return found;
}

void MTriangle::print(){

	for(uint8_t i = 0; i < 3; i++){
		vertices[i].print();
	}
}
