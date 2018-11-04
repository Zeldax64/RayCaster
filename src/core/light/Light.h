#pragma once

#include <iostream>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/color/Color.h"

class Light
{
  Vertex3f pos;
  Color i_amb;
  Color i_intensity;

public:
  Light();
  ~Light();

  virtual void setPosition(const Vertex3f & param)=0;
  virtual void setPosition(float x, float y, float z)=0;

  virtual void setAmbIntensity(float r, float g, float b)=0;
  virtual void setSourceIntensity(float r, float g, float b)=0;

  virtual Vertex3f& getPosition()=0;
  virtual Color* getAmb()=0;
  virtual Color* getSource() =0;

  virtual void applyTransform(const TMatrix & transform)=0;

  virtual void print()=0;
};
