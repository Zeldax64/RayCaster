#pragma once

#include <iostream>

class Color
{
public:
  float colors[3];

  Color();
  Color(float r, float g, float b);
  ~Color();

  void setColor(float r, float g, float b);
  void setRed(float r);
  void setGreen(float g);
  void setBlue(float b);

  float getRed();
  float getGreen();
  float getBlue();

  Color operator + (Color & param);
  Color operator * (const Color & param);
  Color operator * (const float val);

  void print();
};
