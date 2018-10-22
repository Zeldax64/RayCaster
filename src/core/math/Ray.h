#pragma once

#include <iostream>

#include "core/math/Vertex3f.h"

class Ray
{
  Vertex3f origin;
  Vertex3f direction;

public:
  Ray(float d_x, float d_y, float d_z);
  Ray(float o_x, float o_y, float o_z, float d_x, float d_y, float d_z);
  ~Ray();

  void setOrigin(Vertex3f & O);
  void setDirection(Vertex3f & dir);

  Vertex3f& getOrigin();
  Vertex3f& getDirection();

};
