/*
	Face3f Class - Meshes faces
*/

#pragma once

#include <iostream>
#include <stdint.h>

#include "core/math/Vertex3f.h"

class Face3f
{
public:
	uint32_t vertices[3];

	Face3f();
	Face3f(uint32_t v1, uint32_t v2, uint32_t v3);
	~Face3f();
	void setFace(uint32_t v1, uint32_t v2, uint32_t v3);
	void print();
};
