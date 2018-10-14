#pragma once

#include <list>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/objects/Object.h"
#include "core/objects/geometric/GSphere.h"
#include "core/intersect/intersect.h"

class SnowMan : public Object
{
  std::list<Object*> objs;

public:
  SnowMan(float x, float y, float z);
  ~SnowMan();

  void applyTransform(const TMatrix & param);

  float hitObject(Vertex3f & ray);
  float hitObject(Vertex3f & ray, Vertex3f & normal);
  float hitObject(Vertex3f & ray, Vertex3f & ret_n, Material * & ret_mat);

  Material* getMaterial();

  void print();
};
