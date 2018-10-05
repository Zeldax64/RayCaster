#include "core/objects/geometric/GSphere.h"

GSphere::GSphere() { center = Vertex3f(0.0, 0.0, 0.0); radius = 1.0; }
GSphere::GSphere(Vertex3f c, float r, float red, float green, float blue) {
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

bool GSphere::hitObject(Vertex3f & ray, Color & col) {
  // TODO: Finish hit object system
  Vertex3f c = -center;
  float alpha = ray.dotProduct(ray);
  float beta = 2*c.dotProduct(ray);
  float gama = center.dotProduct(center) - radius * radius;

  float delta = beta * beta - 4 * alpha * gama;

  if (delta < 0.0) {
    return false;
  }

  float t_int1 = (-beta + sqrt(delta))/(2 * alpha);
  float t_int2 = (-beta - sqrt(delta))/(2 * alpha);

  if (t_int1 >= 1.0 || t_int2 >= 1.0) {
    col.setColor(material.getRed(),
                 material.getGreen(),
                 material.getBlue());

    return true;
  }
  else {
    return false;
  }
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
