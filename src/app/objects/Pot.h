/*
	Meshes Pot
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

//#define verticessize 44
//#define facessize 80
//#define imax 11
#define PI 3.14159265
class Pot : public Object
{
	Vertex3f *vertices;
	//Edge3f edges[12];
	Face3f *faces;

	Material material;

public:
	Pot();
	Pot(Material & mat);
	~Pot();
	int verticessize;
	int facessize;
	void applyTransform(const TMatrix & param);

	float hitObject(Ray & ray);
 	Material getMaterial(Ray & ray);

	void print();
};
