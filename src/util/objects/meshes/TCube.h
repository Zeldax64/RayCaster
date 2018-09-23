#pragma once

#include <stdint.h>

#include "util/objects/Object.h"
#include "util/math/Vertex3f.h"
#include "util/math/Edge3f.h"
#include "util/math/Face3f.h"

class TCube : Object
{
	Vertex3f vertices[8];
	Edge3f edges[12];
	Face3f faces[12];
public:
	TCube();
	~TCube();
	void applyTransform(const TMatrix & param);

	void print();
};
