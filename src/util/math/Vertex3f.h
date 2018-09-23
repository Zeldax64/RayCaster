/*
	Vertex3f Class

	This class implements a vertex class which can be used to represent a vertex and a vector. Some
	basic operations are also provided.
	TODO:
		- Vertex scalar multiplication;
		- Thinking about whether it's better to use an array[4]
		  instead of variables x, y and z;
*/

#pragma once
#include <math.h>
#include <iostream>

#include "util/math/TMatrix.h"

class Vertex3f
{
public:
	float x, y, z;

	Vertex3f();
	Vertex3f(float new_x, float new_y, float new_z);
	~Vertex3f();
	void moveTo(float new_x, float new_y, float new_z);
	void applyTransform(const TMatrix & param);
	Vertex3f operator + (const Vertex3f & param);
	Vertex3f operator - (const Vertex3f & param);
	// Check whether a matrix multiplication is better than a element to element
	// multiplication when using the "*" operator
	Vertex3f operator * (const Vertex3f & param);

	// TODO: implement scalarProduct
	float scalarProduct(const Vertex3f &param);
	Vertex3f crossProduct(const Vertex3f &param);
	float norm();

	void print();
};
