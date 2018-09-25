#include "core/math/Edge3f.h"

Edge3f::Edge3f() {
}

Edge3f::Edge3f(uint32_t v1, uint32_t v2) {
	vertices[0] = v1;
	vertices[1] = v2;
}

Edge3f::~Edge3f() {
}

void Edge3f::setEdge(uint32_t v1, uint32_t v2) {
	vertices[0] = v1;
	vertices[1] = v2;
}
