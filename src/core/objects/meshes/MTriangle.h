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

  float hitObject(Vertex3f & ray);
  float hitObject(Vertex3f & ray, Vertex3f & normal);
  float hitObject(Vertex3f & ray, Vertex3f & ret_n, Material * & ret_mat);

  Material* getMaterial();
  void setMaterial(Material & new_mat);
  void print();

};
