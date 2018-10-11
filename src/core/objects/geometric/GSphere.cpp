#include "core/objects/geometric/GSphere.h"
#include "core/intersect/intersect.h"

GSphere::GSphere() { center = Vertex3f(0.0, 0.0, 0.0); radius = 1.0; }
GSphere::GSphere(const Vertex3f & c, float r, float red, float green, float blue) {
  center = c;
  radius = r;
  material.setAmb(red, green, blue);
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

float GSphere::hitObject(Vertex3f & ray, Vertex3f & normal) {
  float t = hitSphereRayLength(ray, this);
  if (t >= 1.0) {
    normal = ((ray*t) - this->center).unit();
  }

  return t;
}

float GSphere::hitObject(Vertex3f & ray, Vertex3f & ret_n, Material * & ret_mat) {
  float t = this->hitObject(ray, ret_n);

  ret_mat = this->getMaterial();

  return t;
}

void GSphere::setRadius(float r) { radius = r; }
void GSphere::setCenter(Vertex3f c) { center = c; }
void GSphere::setMaterial(float r, float g, float b) { material.setAmb(r, g, b); }

float GSphere::getRadius() { return radius; }
Vertex3f* GSphere::getCenter() { return &center; }
Material* GSphere::getMaterial() { return &material; }

void GSphere::print() {
  std::cout << "Center: ";
  center.print();
  std::cout << "Radius: " << radius << "\n";
  material.print();
}
