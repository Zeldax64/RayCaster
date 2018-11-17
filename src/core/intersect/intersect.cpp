/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/

#include "core/intersect/intersect.h"

extern int x_line, y_line;
extern bool mouse_debug;
extern bool shadow_debug;

// Iterate through a list of objects to find the best hitted object
float hitObjectList(std::list<Object*> & objs, Ray & ray, Material * & mat, Vertex3f & n) {
  Vertex3f normal; // Normal of the hitted face
  Vertex3f best_normal; // Normal of the hitted face
  Material* new_mat;
  Material* best_mat = NULL;
  Object* best_obj = NULL;
  float best_t = FLT_MAX;

  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    float t = (*it)->hitObject(ray, normal, new_mat);

    if(ray.updateLength(t)) {
      best_t = t;
      best_normal = normal;
      best_mat = new_mat;
      best_obj = (*it);
      ray.setHittedObject(best_obj);
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

  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    float t = (*it)->hitObject(ray, normal, new_mat);

    if(t < best_t && t >= 1e-4) { // t >= 1e-4 To solve shadow acne problem
      best_t = t;

    }
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
float hitTriangle(Ray & ray, Vertex3f & v0, Vertex3f & v1, Vertex3f & v2, float & out_u, float & out_v) {
  // TM Algorithm!
  Vertex3f ray_dir = ray.getDirection();
  Vertex3f ray_org = ray.getOrigin();

  Vertex3f v0_n = v0;
  Vertex3f v1_n = v1;
  Vertex3f v2_n = v2;

  const float EPSILON = 0.00000001;
  Vertex3f edge1, edge2, h, s, q;
  float a, f, u, v;
  edge1 = v1_n - v0_n;
  edge2 = v2_n - v0_n;

  h = ray_dir.crossProduct(edge2);
  a = edge1.dotProduct(h);
  if (a > -EPSILON && a < EPSILON) {// This ray is parallel to this triangle.
    if(mouse_debug && shadow_debug) {
      //std::cout << "Test: failed on 'a' test \n";
    }
    return -1.0;
  }

  f = 1.0/a;
  s = ray_org - v0_n;
  u = f * (s.dotProduct(h));
  if (u < 0.0 || u > 1.0) {
    if(mouse_debug && shadow_debug) {
      //std::cout << "Test: failed on 'u' test \n";
    }
    return -1.0;
  }

  q = s.crossProduct(edge1);
  v = f * ray_dir.dotProduct(q);
  if (v < 0.0 || (u + v) > 1.0) {
    if(mouse_debug && shadow_debug) {
      //std::cout << "Test: failed on 'v < 0.0 (u+v)' test \n";
    }
    return -1.0;
  }

  // At this stage we can compute t to find out where the intersection point is on the line.
  float t = f * edge2.dotProduct(q);
    if (t > EPSILON) // ray intersection
    {
      out_u = u;
      out_v = v;
      return t;
    }
    else // This means that there is a line intersection but not a ray intersection.
      return -1.0;
}

float hitTriangles(Ray & ray, Object * obj, Vertex3f * vertices, Face3f * faces, uint32_t faces_num, Vertex3f & ret_n, Material * & ret_mat) {
  float best_t = FLT_MAX;
  int best_face = -1;
  Vertex3f vector = ray.getDirection();
  float best_u = 0.0;
  float best_v = 0.0;

  for (uint32_t i = 0; i < faces_num; i++) {
      Face3f face = faces[i];
      Vertex3f v0 = vertices[face.vertices[0]];
      Vertex3f v1 = vertices[face.vertices[1]];
      Vertex3f v2 = vertices[face.vertices[2]];

      Vertex3f n = (v1-v0).crossProduct(v2-v0);

      // Backface culling:
      if(n.unit().dotProduct(-(ray.getDirection())) < 0.0) {
        continue;
      }
      float u, v;
      float tint = hitTriangle(ray, v0, v1, v2, u, v);

      if (ray.updateLength(tint)) {
        best_t = tint;
        ret_mat = obj->getMaterial();
        ret_n = n;

        best_face = i;
        best_u = u;
        best_v = v;

        ray.setUV(u, v);
        ray.setHittedFace(best_face);
        ray.setHittedObject(obj);

        if(mouse_debug && !shadow_debug) {
          std::cout << "hitFirstObjectListe(): T: " << tint <<"\n";
        }
        if(mouse_debug && !shadow_debug) {
          std::cout << "hitFirstObjectList(): t: " << best_t << " Face: " << best_face <<"\n";
        }
      }
    }

  if(mouse_debug && shadow_debug) {
    std::cout << "-> hitTriangles(shadow) best_t: " << best_t <<"\n";
  }
  if(ray.getHittedFace() != best_face) {

  }
  return best_t;
}
