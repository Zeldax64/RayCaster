/*
	Object Class - Abstract
*/

#pragma once

#include "util/math/TMatrix.h"

class Object
{

public:
	Object();
	~Object();

	virtual void applyTransform(const TMatrix & param)=0;
};
