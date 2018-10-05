#pragma once

#include <iostream>
#include "core/color/Color.h"

class Material
{
  Color col;
public:
  Material();
  ~Material();

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
