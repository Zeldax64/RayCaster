#pragma once

#include <iostream>
#include <vector>
#include <stdint.h>
#include <float.h>

#include "core/objects/Object.h"
#include "core/math/Vertex3f.h"
#include "core/math/Edge3f.h"
#include "core/math/Face3f.h"
#include "core/color/Color.h"
#include "core/material/Material.h"
#include "core/intersect/intersect.h"
#include "core/math/Ray.h"
#include "util/objloader.h"

class MObj : public Object
{
  Vertex3f* vertices;
  uint32_t vertices_num;
  Face3f* faces;
  uint32_t faces_num;

  Material material;

public:
  MObj();
  ~MObj();
  void applyTransform(const TMatrix & param);

	float hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat);
  Material* getMaterial();

	void print();
  bool loadObj(const char * path);

};
