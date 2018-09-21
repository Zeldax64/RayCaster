/*
	Vertex3f Class

	This class implements a vertex class which can be used to represent a vertex and a vector. Some
	basic operations are also provided.
	TODO:
		- Vertex multiplication;
		- Scalar product of two vectors;
*/

#pragma once
#include <math.h>

class Vertex3f
{
public:
	float x, y, z;

	Vertex3f();
	Vertex3f(float new_x, float new_y, float new_z);
	~Vertex3f();
	Vertex3f operator + (const Vertex3f & param);
	Vertex3f operator - (const Vertex3f & param);
	// Check whether a matrix multiplication is better than a element to element
	// multiplication when using the "*" operator
	Vertex3f operator * (const Vertex3f & param);
	
	float norm();


};

