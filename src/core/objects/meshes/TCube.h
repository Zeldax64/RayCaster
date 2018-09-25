#pragma once

#include <stdint.h>

#include "core/objects/Object.h"
#include "core/math/Vertex3f.h"
#include "core/math/Edge3f.h"
#include "core/math/Face3f.h"

class TCube : public Object
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
