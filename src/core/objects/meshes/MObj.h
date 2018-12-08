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
#include "core/texture/Texture.h"
#include "util/objloader.h"

class MObj : public Object
{
  Vertex3f* vertices = NULL;
  uint32_t vertices_num;
  Face3f* faces = NULL;
  uint32_t faces_num;

  Material material;
  Texture* texture;

public:
  MObj();
  ~MObj();
  void applyTransform(const TMatrix & param);
	float hitObject(Ray & ray);
  Material getMaterial(Ray &ray);
	void print();

  bool loadObj(const char * path);
};
