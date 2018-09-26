/*
	Vertex3f Class

	This class implements a vertex class which can be used to represent a vertex and a vector. Some
	basic operations are also provided.
	TODO:
		- Vertex scalar multiplication;
		- Thinking about whether it's better to use an array[4]
		  instead of variables x, y and z;
		- Method to return normal of a Vector;
*/

#pragma once
#include <math.h>
#include <iostream>

// Forward declaration of TMatrix
class TMatrix;

#include "core/math/TMatrix.h"

class Vertex3f
{
public:
	float x, y, z;

	Vertex3f();
	Vertex3f(float new_x, float new_y, float new_z);
	~Vertex3f();
	void moveTo(float new_x, float new_y, float new_z);
	void applyTransform(const TMatrix & param);
	Vertex3f operator - (void) const;
	Vertex3f operator + (const Vertex3f & param);
	Vertex3f operator - (const Vertex3f & param);
	// Check whether a matrix multiplication is better than a element to element
	// multiplication when using the "*" operator
	Vertex3f operator * (const Vertex3f & param);
	Vertex3f operator / (const float & param);

	// TODO: implement scalarProduct
	float dotProduct(const Vertex3f &param);
	Vertex3f crossProduct(const Vertex3f &param);
	float length();
	Vertex3f unit();

	// Setters
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	// Getters
	float getX();
	float getY();
	float getZ();

	void print();
};
