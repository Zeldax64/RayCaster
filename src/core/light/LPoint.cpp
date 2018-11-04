#include "core/light/LPoint.h"

LPoint::LPoint() {
    this->setAmbIntensity(0.0, 0.0, 0.0);
    this->setSourceIntensity(0.0, 0.0, 0.0);
}

LPoint::~LPoint() {}

void LPoint::setPosition(const Vertex3f & param) { pos = param; }
void LPoint::setPosition(float x, float y, float z) { pos.moveTo(x, y, z); }


void LPoint::setAmbIntensity(float r, float g, float b) {
  i_amb.setColor(r, g, b);
}

void LPoint::setSourceIntensity(float r, float g, float b) {
  i_intensity.setColor(r, g, b);
}

Vertex3f& LPoint::getPosition() { return pos; }
Color* LPoint::getAmb() { return &i_amb; }
Color* LPoint::getSource() { return &i_intensity; }

void LPoint::applyTransform(const TMatrix & transform) {
  pos.applyTransform(transform);
}

void LPoint::print() {
  std::cout << "Position: "; pos.print();
  i_amb.print();
  i_intensity.print();
}
