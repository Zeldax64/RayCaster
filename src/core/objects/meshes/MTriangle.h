/*
	Meshes Cube
*/

#pragma once

#include <stdint.h>

#include "core/objects/Object.h"
#include "core/math/Vertex3f.h"
#include "core/math/Edge3f.h"
#include "core/math/Face3f.h"
#include "core/color/Color.h"
#include "core/intersect/intersect.h"
#include "core/math/Ray.h"

class MTriangle : public Object
{
  Vertex3f vertices[3];
  Edge3f edges[3];
  Face3f faces[1];

  Material material;

public:
  MTriangle();
  MTriangle(Material & mat);
  ~MTriangle();
  void applyTransform(const TMatrix & param);

  float hitObject(Ray & ray);

  Material getMaterial(Ray &ray);
  void setMaterial(Material & new_mat);

  void print();

};
