#pragma once

#include <iostream>

#include "core/math/Vertex3f.h"

class Ray
{
  Vertex3f origin;
  Vertex3f direction;

public:
  Ray(Vertex3f & direction);
  Ray(Vertex3f & origin, Vertex3f & direction);
  Ray(float d_x, float d_y, float d_z);
  Ray(float d_x, float d_y, float d_z, float o_x, float o_y, float o_z);
  ~Ray();

  void setOrigin(Vertex3f & O);
  void setDirection(Vertex3f & dir);

  Vertex3f& getOrigin();
  Vertex3f& getDirection();

  void print();
};
