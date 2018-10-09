#pragma once

#include <iostream>
#include "core/color/Color.h"

class Material
{
  Color k_amb; // Material ambient constant
  Color k_dif; // Material diffusal constant
  Color k_esp; // Material specular constant

public:
  Material();
  ~Material();

  void setAmb(float r, float g, float b);
  void setDif(float r, float g, float b);
  void setEsp(float r, float g, float b);

  Color* getAmb();
  Color* getDif();
  Color* getEsp();

  void print();
};
