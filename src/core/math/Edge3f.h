/*
	Edge3f Class - Meshes faces
*/

#pragma once

#include <stdint.h>

class Edge3f
{
	uint32_t vertices[2];
public:
	Edge3f();
	Edge3f(uint32_t v1, uint32_t v2);
	~Edge3f();
	void setEdge(uint32_t v1, uint32_t v2);

};
