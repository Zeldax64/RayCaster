#include "core/objects/geometric/GSphere.h"
#include "core/intersect/intersect.h"

GSphere::GSphere() { center = Vertex3f(0.0, 0.0, 0.0); radius = 1.0; }

GSphere::GSphere(const Vertex3f & c, float r, Material & mat) {
  center = c;
  radius = r;
  material = mat;
 }
GSphere::~GSphere() { }

void GSphere::applyTransform(const TMatrix & param) {
  center.applyTransform(param);
  // TODO: apply transform to a point on the sphere's shell also!
  // By doing this it'll be possible to handle scale transformations
}

float GSphere::hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat) {
  Vertex3f ray_dir = ray.getDirection();

  float t = hitSphereRayLength(ray, this);
  if (t >= 1.0) {
    ret_n = ((ray_dir*t) - this->center).unit();
  }
  ret_mat = this->getMaterial();

  return t;
}

void GSphere::setRadius(float r) { radius = r; }
void GSphere::setCenter(Vertex3f c) { center = c; }
void GSphere::setMaterial(Material & new_mat) { this->material = new_mat; }

float GSphere::getRadius() { return radius; }
Vertex3f* GSphere::getCenter() { return &center; }
Material* GSphere::getMaterial() { return &material; }

Material GSphere::getTexturedMaterial(uint32_t face, float u, float v) {
  return *(this->getMaterial());
}

void GSphere::print() {
  std::cout << "Center: ";
  center.print();
  std::cout << "Radius: " << radius << "\n";
  std::cout << "Material:\n";
  material.print();
}
