#include "core/math/Ray.h"

Ray::Ray(float d_x, float d_y, float d_z) {
  origin.moveTo(0, 0, 0);
  direction.moveTo(d_x, d_y, d_z);
}

Ray::Ray(float o_x, float o_y, float o_z, float d_x, float d_y, float d_z) {
  origin.moveTo(o_x, o_y, o_z);
  direction.moveTo(d_x, d_y, d_z);
}

Ray::~Ray() {}

Vertex3f& Ray::getOrigin() { return origin; }

Vertex3f& Ray::getDirection() { return direction; }
