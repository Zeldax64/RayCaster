#pragma once

#include <iostream>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/color/Color.h"
#include "core/light/Light.h"

class LPoint : public Light
{
  Vertex3f pos;
  Color i_amb;
  Color i_intensity;

public:
  LPoint();
  ~LPoint();

  void setPosition(const Vertex3f & param);
  void setPosition(float x, float y, float z);

  void setAmbIntensity(float r, float g, float b);
  void setSourceIntensity(float r, float g, float b);

  Vertex3f& getPosition();
  Color* getAmb();
  Color* getSource();

  void applyTransform(const TMatrix & transform);

  void print();
};
