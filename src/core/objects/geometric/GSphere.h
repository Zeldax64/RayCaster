#pragma once

#include <iostream>

#include <stdint.h>
#include <math.h>

#include "core/objects/Object.h"
#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/color/Color.h"
#include "core/material/Material.h"


class GSphere : public Object
{
  float radius;
  Vertex3f center;
  Material material;

public:
	GSphere();
  GSphere(const Vertex3f & c, float r, Material & mat);
	~GSphere();

	void applyTransform(const TMatrix & param);

  float hitObject(Ray & ray);

  Material getMaterial(Ray & ray);

  void print();

  void setRadius(float r);
  void setCenter(Vertex3f c);
  void setMaterial(Material & new_mat);


  float getRadius();
  Vertex3f* getCenter();

};
