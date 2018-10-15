#pragma once

#include <iostream>
#include "core/color/Color.h"

class Material
{
  Color k_amb; // Material ambient constant
  Color k_dif; // Material diffusal constant
  Color k_spe; // Material specular constant

public:
  Material();
  Material(float ar, float ag, float ab,
           float dr, float dg, float db,
           float sr, float sg, float sb);

  ~Material();

  void setAmb(float r, float g, float b);
  void setDif(float r, float g, float b);
  void setSpe(float r, float g, float b);

  Color* getAmb();
  Color* getDif();
  Color* getSpe();

  void operator = (Material & param);

  void print();
};
