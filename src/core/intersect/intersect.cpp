/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/

#include "core/intersect/intersect.h"

// Iterate through a list of objects to find the best hitted object
float hitObjectList(std::list<Object*> & objs, Ray & ray, Material * & mat, Vertex3f & n) {
  Vertex3f normal; // Normal of the hitted face
  Vertex3f best_normal; // Normal of the hitted face
  Material* new_mat;
  Material* best_mat = NULL;
  float best_t = FLT_MAX;
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    float t = (*it)->hitObject(ray, normal, new_mat);

    if(t <= best_t && t >= 0.0) {
      best_t = t;
      best_normal = normal;
      best_mat = new_mat;
    }
  }

  if(best_t < FLT_MAX) {
    n = best_normal.unit();
    mat = best_mat;
  }

  return best_t;
}

// Iterate through a list of objects and return the t at the first hit
// Can be used to compute shadows
// TODO: Fix this function! It must return the t of the fisrt object hitted
// but the object must be between the origin of the ray and the light source.
// The light source position must be included in this function.
float hitFirstObjectList(std::list<Object*> & objs, Ray & ray) {
  Vertex3f normal; // Normal of the hitted face
  Material* new_mat;
  float best_t = FLT_MAX;

  int i = 0;
  int best_i = -1;
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    float t = (*it)->hitObject(ray, normal, new_mat);

    if(t < best_t && t >= 1e-4) { // t >= 1e-4 To solve shadow acne problem
      best_t = t;

      best_i = i;
    }
    i++;
  }
  if(best_i != -1) {
    std::cout << "Obj" << best_i << " melhor! t = "<< best_t << "\n";
  }
  return best_t;
}

// Can be used with a sphere cluster
float hitSphere(Ray & ray, GSphere* sphere) {
  Vertex3f ray_dir = ray.getDirection();
  Vertex3f ray_org = ray.getOrigin();

  Vertex3f center = (*sphere->getCenter()) - ray_org;
  float radius = sphere->getRadius();
  Vertex3f c = -( center);
  float alpha = ray_dir.dotProduct(ray_dir);
  float beta = 2*c.dotProduct(ray_dir);
  float gama = ( center).dotProduct( center) - radius * radius;

  float delta = beta * beta - 4 * alpha * gama;

  return delta;
}

float hitSphereRayLength(Ray & ray, GSphere* sphere) {
  Vertex3f ray_dir = ray.getDirection();
  Vertex3f ray_org = ray.getOrigin();

  Vertex3f center = (*sphere->getCenter()) - ray_org;
  float radius = sphere->getRadius();
  Vertex3f c = -(center);
  float alpha = ray_dir.dotProduct(ray_dir);
  float beta = 2*c.dotProduct(ray_dir);
  float gama = (center).dotProduct(center) - radius * radius;

  float delta = beta * beta - 4 * alpha * gama;

  float t_int1 = (-beta - sqrt(delta))/(2 * alpha);
  float t_int2 = (-beta + sqrt(delta))/(2 * alpha);

  if (t_int1 >= 0.0) {
    return t_int1;
  }
  if (t_int2 >= 0.0) {
    return t_int2;
  }
  return -1.0;
}

// Triangles
float hitTriangle(Ray & ray, Vertex3f & v0, Vertex3f & v1, Vertex3f & v2, Vertex3f & ret_n) {
  // TM Algorithm!
  Vertex3f ray_dir = ray.getDirection();
  Vertex3f ray_org = ray.getOrigin();

  Vertex3f v0_n = v0;
  Vertex3f v1_n = v1;
  Vertex3f v2_n = v2;

  const float EPSILON = 0.0000001;
  Vertex3f edge1, edge2, h, s, q;
  float a, f, u, v;
  edge1 = v1_n - v0_n;
  edge2 = v2_n - v0_n;
  h = ray_dir.crossProduct(edge2);
  a = edge1.dotProduct(h);
  if (a > EPSILON && a < EPSILON)
    return -1.0;

  f = 1.0/a;
  s = ray_org - v0_n;
  u = f * (s.dotProduct(h));
  if (u < 0.0 || u > 1.0)
      return -1.0;

  q = s.crossProduct(edge1);
  v = f * ray_dir.dotProduct(q);
  if (v < 0.0 || u + v > 1.0)
    return -1.0;

  // At this stage we can compute t to find out where the intersection point is on the line.
  float t = f * edge2.dotProduct(q);
    if (t > EPSILON) // ray intersection
    {
      ret_n = edge1.crossProduct(edge2);
      return t;
    }
    else // This means that there is a line intersection but not a ray intersection.
      return -1.0;

  /*----- End of TM algorithm -----*/

  /*
  Vertex3f u = v1_n - v0_n;
	Vertex3f v = v2_n - v0_n;

  Vertex3f n = (u.crossProduct(v)).unit();

  // Calculate intersection point of ray and plane
  float tint = v0_n.dotProduct(n) / ray_dir.dotProduct(n);
  //std::cin.get();
  // TODO: Check if this if is correct or not
  if (tint < 0.0) {
    return -1.0;
  }
  Vertex3f Pi = ray_dir * tint;
  // TODO: Possible improvement
  // If ray * n -> 0, then Pi -> infinity. A check could be done here
  // like ray . n == 0;

  // Calculate whether the point is in the triangle
  // Partial dot products
  Vertex3f w = Pi - v0;

  float a = u.dotProduct(v); // a = (u . v);
  float b = w.dotProduct(v); // b = (w . v);
  float c = v.dotProduct(v); // c = (v . v);
  float d = w.dotProduct(u); // d = (w . u);
  float e = u.dotProduct(u); // e = (u . u);
  float den = a * a - e * c; // Denominator

  float si = (a * b - c * d) / den;
  float ti = (a * d - e * b) / den;

  // TODO: improve hit checking to allow diferences between hidden faces
  if (si >= 0.0 && ti >= 0.0 && si+ti <= 1.0) {
    ret_n = n;
    return tint;
  }
  return -1.0;
  */
}

float hitTriangles(Ray & ray, Object * obj, Vertex3f * vertices, Face3f * faces, uint32_t faces_num, Vertex3f & ret_n, Material * & ret_mat) {
  float best_t = FLT_MAX;

  for (uint32_t i = 0; i < faces_num; i++) {
    Face3f face = faces[i];
    Vertex3f v0 = vertices[face.vertices[0]];
    Vertex3f v1 = vertices[face.vertices[1]];
    Vertex3f v2 = vertices[face.vertices[2]];

    Vertex3f n;

    float tint = hitTriangle(ray, v0, v1, v2, n);

    if (tint >= 0.0 && tint < best_t) {
      best_t = tint;
      ret_mat = obj->getMaterial();
      ret_n = n;
    }
  }
  return best_t;
}
