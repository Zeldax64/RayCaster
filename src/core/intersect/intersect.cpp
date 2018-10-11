/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/

#include "core/intersect/intersect.h"

// Iterate through a list of objects to find the best hitted object
float hitObjectList(std::list<Object*> & objs, Vertex3f ray, Material * & mat, Vertex3f & n) {
  Vertex3f normal; // Normal of the hitted face
  Vertex3f best_normal; // Normal of the hitted face
  Material* new_mat;
  Material* best_mat;
  float best_t = FLT_MAX;
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    float t = (*it)->hitObject(ray, normal, new_mat);

    if(t <= best_t && t >= 1.0) {

      //(*it)->print();
      best_t = t;
      best_normal = normal;
      best_mat = new_mat;
    }
  }

// TODO: Compare the result of this code with the current
// method implemented in RayCasting.cpp
  if(best_t < FLT_MAX) {
    n = best_normal.unit();
    mat = best_mat;
  }

  return best_t;
}

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

  float t_int1 = (-beta - sqrt(delta))/(2 * alpha);
  float t_int2 = (-beta + sqrt(delta))/(2 * alpha);

  if (t_int1 >= 1.0) {
    return t_int1;
  }
  else {
    return t_int2;
  }
}
