#pragma once

class Color
{
  float colors[3]; // R = color

public:
  Color();
  Color(float r, float g, float b);
  ~Color();

  void setColor(float r, float g, float b);
  float getRed();
  float getGreen();
  float getBlue();

};
