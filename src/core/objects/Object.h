/*
	Object Class - Abstract
*/

#pragma once

#include "core/math/TMatrix.h"
#include "core/math/Vertex3f.h"
#include "core/color/Color.h"

class Object
{

public:
	Object();
	~Object();

	virtual void applyTransform(const TMatrix & param)=0;
	virtual bool hitObject(Vertex3f & ray, Color & col)=0;
	virtual void print()=0;
};
