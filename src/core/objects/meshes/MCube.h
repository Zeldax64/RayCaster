/*
	Meshes Cube
*/

#pragma once

#include <stdint.h>
#include <float.h>

#include "core/objects/Object.h"
#include "core/math/Vertex3f.h"
#include "core/math/Edge3f.h"
#include "core/math/Face3f.h"
#include "core/color/Color.h"
#include "core/material/Material.h"
#include "core/intersect/intersect.h"
#include "core/math/Ray.h"

class MCube : public Object
{
	Vertex3f vertices[8];
	Edge3f edges[12];
	Face3f faces[12];

	Material material;

public:
	MCube();
	MCube(Material & mat);
	~MCube();
	void applyTransform(const TMatrix & param);

	float hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat);
  Material* getMaterial();

	void print();
};
