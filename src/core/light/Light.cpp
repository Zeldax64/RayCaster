#include "core/light/Light.h"

Light::Light() {
    col.setColor(1.0, 1.0, 1.0);
}

Light::~Light() {}

void Light::setPosition(const Vertex3f & param) { pos = param; }

void Light::setColor(float r, float g, float b) {
  col.setColor(r, g, b);
}

void Light::setRed(float r) {
  col.setRed(r);
}

void Light::setGreen(float g) {
  col.setGreen(g);
}

void Light::setBlue(float b) {
  col.setBlue(b);
}

Color* Light::getColor() { return &col; }
float Light::getRed() { return col.getRed(); }
float Light::getGreen() { return col.getGreen(); }
float Light::getBlue() {return col.getBlue(); }

void Light::print() {
  std::cout << "Position: "; pos.print();
  col.print();
}
