#pragma once

#include <iostream>
#include "core/math/Vertex3f.h"
#include "core/color/Color.h"

class Light
{
  Vertex3f pos;
  Color col;
public:
  Light();
  ~Light();

  void setPosition(const Vertex3f & param);

  void setColor(float r, float g, float b);
  void setRed(float r);
  void setGreen(float g);
  void setBlue(float b);

  Color* getColor();
  float getRed();
  float getGreen();
  float getBlue();

  void print();
};
