/*
	TMatrix Class - Transformation Matrix

	This class implements the matrices used to apply transformations on data structures.
	TODO:
	- Check whether a implementation using only one rotation (as done in OpenGL) is better
	than a rotation to each axis (as done now);
	- Implement Shear operation?
	- Check whether a implementation using stack-like transformations as done in OpenGL is
	better;

*/

#pragma once

#include <math.h>
#include <iostream>


class TMatrix
{

	void identity();
	float convertToRadians(float theta);
public:
	float matrix[4][4];

	TMatrix();
	~TMatrix();

	void scale(float x, float y, float z);
	void translate(float x, float y, float z);
	void rotateX(float theta);
	void rotateY(float theta);
	void rotateZ(float theta);
	//TODO: Fix coordTransform. Thinking about creating two transformations W->L and L-W
	//void coordTransform(const Vertex3f & x, const Vertex3f & y, const Vertex3f & z, const Vertex3f & e);
	void print();

	TMatrix operator * (const TMatrix & param);
};
