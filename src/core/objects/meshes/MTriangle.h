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
public:
  MTriangle();
  ~MTriangle();
  void applyTransform(const TMatrix & param);

  bool hitObject(Vertex3f & ray, Color & col);
  void print();

};
