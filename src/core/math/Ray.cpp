#include "core/math/Ray.h"

Ray::Ray() {
  origin.moveTo(0, 0, 0);
  direction.moveTo(0, 0, 0);
}

Ray::Ray(Vertex3f & direction) {
  origin.moveTo(0, 0, 0);
  this->direction = direction;
}

Ray::Ray(Vertex3f & origin, Vertex3f & direction) {
  this->origin = origin;
  this->direction = direction;
}

Ray::Ray(float d_x, float d_y, float d_z) {
  origin.moveTo(0, 0, 0);
  direction.moveTo(d_x, d_y, d_z);
}

Ray::Ray(float o_x, float o_y, float o_z, float d_x, float d_y, float d_z) {
  origin.moveTo(o_x, o_y, o_z);
  direction.moveTo(d_x, d_y, d_z);
}

Ray::~Ray() {}

void Ray::setOrigin(float o_x, float o_y, float o_z) {
  origin.moveTo(o_x, o_y, o_z);
}
void Ray::setDirection(float d_x, float d_y, float d_z) {
  direction.moveTo(d_x, d_y, d_z);
}
void Ray::setOrigin(Vertex3f & O) { this->origin = O; }
void Ray::setDirection(Vertex3f & dir) { this->direction = dir; }

Vertex3f& Ray::getOrigin() { return origin; }
Vertex3f& Ray::getDirection() { return direction; }

void Ray::print() {
  std::cout << "Origin = ";
  origin.print();
  std::cout << "Direction = ";
  direction.print();
}
