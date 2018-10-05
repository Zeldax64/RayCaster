/*
	Object Class - Abstract
*/

#pragma once

#include "core/math/TMatrix.h"
#include "core/math/Vertex3f.h"
#include "core/color/Color.h"
#include "core/material/Material.h"

class Object
{

public:
	Object();
	~Object();

	virtual void applyTransform(const TMatrix & param)=0;
	virtual float hitObject(Vertex3f & ray)=0;
	virtual Material* getMaterial()=0;
	virtual void print()=0;
};
