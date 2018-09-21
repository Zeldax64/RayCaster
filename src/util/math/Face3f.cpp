#include "Face3f.h"

Face3f::Face3f() {
}

Face3f::Face3f(uint32_t v1, uint32_t v2, uint32_t v3) {
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
}

Face3f::~Face3f() {
}

void Face3f::setFace(uint32_t v1, uint32_t v2, uint32_t v3) {
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
}