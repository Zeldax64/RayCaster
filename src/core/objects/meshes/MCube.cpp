#include "MCube.h"

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

	faces[0].setFace(0, 1, 2);
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
}

MCube::~MCube() {
}

void MCube::applyTransform(const TMatrix & param) {
	for(uint8_t i = 0; i < 8; i++){
		vertices[i].applyTransform(param);
	}
}

// TODO: This method will produce a full red square
bool MCube::hitObject(Vertex3f & ray, Color & col) {
	bool found = false;

	for(uint8_t i = 0; i < 12; i++) {


		Face3f face = faces[i];
		Vertex3f v0 = vertices[face.vertices[0]];
		Vertex3f v1 = vertices[face.vertices[1]];
		Vertex3f v2 = vertices[face.vertices[2]];

		Vertex3f u = v1 - v0;
		Vertex3f v = v2 - v0;

		Vertex3f n = (v1.crossProduct(v2)).unit();

		/* Calculate intersection point of ray and plane */
		float tint = v0.dotProduct(n) / ray.dotProduct(n);
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
		if (si >= 0 && ti >= 0 && si+ti <= 1) {
			found = true;
			col.setColor(1.0, 0.0, 0.0); // Setting red
			return found;
		}
	}
	return found;
}


void MCube::print(){
	
	for(uint8_t i = 0; i < 8; i++){
		vertices[i].print();
	}
}
