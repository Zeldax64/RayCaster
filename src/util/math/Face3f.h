/*
	Face3f Class - Meshes faces
*/

#pragma once

#include <stdint.h>

#include "util/math/Vertex3f.h"

class Face3f
{
	uint32_t vertices[3];
public:
	Face3f();
	Face3f(uint32_t v1, uint32_t v2, uint32_t v3);
	~Face3f();
	void setFace(uint32_t v1, uint32_t v2, uint32_t v3);
};