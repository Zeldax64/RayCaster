/*
	Object Class - Abstract
*/

#pragma once

#include "core/math/TMatrix.h"

class Object
{

public:
	Object();
	~Object();

	virtual void applyTransform(const TMatrix & param)=0;
	virtual void print()=0;
};
