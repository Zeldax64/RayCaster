#include "core/light/Light.h"

Light::Light() {
    this->setAmbIntensity(0.0, 0.0, 0.0);
    this->setSourceIntensity(0.0, 0.0, 0.0);
}

Light::~Light() {}

void Light::setPosition(const Vertex3f & param) { pos = param; }
void Light::setPosition(float x, float y, float z) { pos.moveTo(x, y, z); }


void Light::setAmbIntensity(float r, float g, float b) {
  i_amb.setColor(r, g, b);
}

void Light::setSourceIntensity(float r, float g, float b) {
  i_intensity.setColor(r, g, b);
}

Vertex3f* Light::getPosition() { return &pos; }
Color* Light::getAmb() { return &i_amb; }
Color* Light::getSource() { return &i_intensity; }

void Light::applyTransform(const TMatrix & transform) {
  pos.applyTransform(transform);
}

void Light::print() {
  std::cout << "Position: "; pos.print();
  i_amb.print();
}
