/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/

#include "core/intersect/intersect.h"

// Can be used with a sphere cluster
float hitSphere(Vertex3f & ray, GSphere* sphere) {
  Vertex3f* center = sphere->getCenter();
  float radius = sphere->getRadius();
  Vertex3f c = -(*center);
  float alpha = ray.dotProduct(ray);
  float beta = 2*c.dotProduct(ray);
  float gama = (*center).dotProduct(*center) - radius * radius;

  float delta = beta * beta - 4 * alpha * gama;

  return delta;
}

float hitSphereRayLength(Vertex3f & ray, GSphere* sphere) {
  Vertex3f* center = sphere->getCenter();
  float radius = sphere->getRadius();
  Vertex3f c = -(*center);
  float alpha = ray.dotProduct(ray);
  float beta = 2*c.dotProduct(ray);
  float gama = (*center).dotProduct(*center) - radius * radius;

  float delta = beta * beta - 4 * alpha * gama;

  float t_int1 = (-beta + sqrt(delta))/(2 * alpha);
  float t_int2 = (-beta - sqrt(delta))/(2 * alpha);

  if (t_int1 >= 1.0) {
    return t_int1;
  }
  else {
    return t_int2;
  }
}
