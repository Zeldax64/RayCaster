/*
	Object Class - Abstract
*/

#pragma once

#include <stdint.h>

#include "core/math/TMatrix.h"
#include "core/math/Vertex3f.h"
#include "core/color/Color.h"
#include "core/material/Material.h"
#include "core/math/Ray.h"

class Object
{

public:
	Object();
	~Object();

	virtual void applyTransform(const TMatrix & param)=0;
	virtual float hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat)=0;
	//virtual float hitObject(Ray & ray, Object * & out_obj, uint32_t & out_face, float & out_u, float & out_v)=0;

	virtual Material* getMaterial()=0;
	//virtual Material getTexturedMaterial(uint32_t face, float u, float v)=0;

	virtual void print()=0;
};
