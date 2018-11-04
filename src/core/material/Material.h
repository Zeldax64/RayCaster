#pragma once

#include <iostream>

#include <math.h>

#include "core/color/Color.h"

class Material
{
  Color k_amb; // Material ambient constant
  Color k_dif; // Material diffusal constant
  Color k_spe; // Material specular constant
  float spe_exp;

public:
  Material();
  Material(float ar, float ag, float ab,
           float dr, float dg, float db,
           float sr, float sg, float sb, float s_exp);

  ~Material();

  void setAmb(float r, float g, float b);
  void setDif(float r, float g, float b);
  void setSpe(float r, float g, float b, float s_exp);

  Color* getAmb();
  Color* getDif();
  Color* getSpe();
  float getSpeExp();

  void operator = (Material & param);

  void print();
};
