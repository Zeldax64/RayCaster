#include "core/objects/geometric/GSphere.h"
#include "core/intersect/intersect.h"

GSphere::GSphere() { center = Vertex3f(0.0, 0.0, 0.0); radius = 1.0; }
GSphere::GSphere(const Vertex3f & c, float r, float red, float green, float blue) {
  center = c;
  radius = r;
  material.setColor(red, green, blue);
 }
GSphere::~GSphere() { }

void GSphere::applyTransform(const TMatrix & param) {
  center.applyTransform(param);
  // TODO: apply transform to a point on the sphere's shell also!
  // By doing this it'll be possible to handle scale transformations
}

float GSphere::hitObject(Vertex3f & ray) {
  float t = hitSphereRayLength(ray, this);
  return t;
}

void GSphere::setRadius(float r) { radius = r; }
void GSphere::setCenter(Vertex3f c) { center = c; }
void GSphere::setMaterial(float r, float g, float b) { material.setColor(r, g, b); }

float GSphere::getRadius() { return radius; }
Vertex3f* GSphere::getCenter() { return &center; }
Material* GSphere::getMaterial() { return &material; }

void GSphere::print() {
  std::cout << "Center: ";
  center.print();
  std::cout << "Radius: " << radius << "\n";
  material.print();
}
