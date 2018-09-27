#include "core/color/Color.h"

Color::Color() { setColor(0.0, 0.0, 0.0); }

Color::Color(float r, float g, float b) { setColor(r, g, b); }

Color::~Color() {}

void Color::setColor(float r, float g, float b) {
  colors[0] = r;
  colors[1] = g;
  colors[2] = b;
}

float Color::getRed() { return colors[0]; }
float Color::getGreen() { return colors[1]; }
float Color::getBlue() { return colors[2]; }
