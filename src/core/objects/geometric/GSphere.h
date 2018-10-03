#pragma once

#include <iostream>
#include <math.h>

#include "core/objects/Object.h"
#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/color/Color.h"

class GSphere : public Object
{
  float radius;
  Vertex3f center;

public:
	GSphere();
  GSphere(Vertex3f c, float r);
	~GSphere();

	void applyTransform(const TMatrix & param);

//	Color hitObject
/*
	Implement hitObject function. It must check all faces and find the first
	hitted by the ray; It returns a color.
	Maybe returning the color of the hitted face's material and the point where it were
	hitted will be a better implementation then the caller method will handle
	any illumination issue
*/
	bool hitObject(Vertex3f & ray, Color & col);

  void setRadius(float r);
  void setCenter(Vertex3f c);
  float getRadius();
  Vertex3f getCenter();

	void print();
};
