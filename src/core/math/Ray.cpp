#include "core/math/Ray.h"

Ray::Ray() {
  origin.moveTo(0, 0, 0);
  direction.moveTo(0, 0, 0);
  hitted_face = -1;
  hitted_obj = NULL;
}

Ray::Ray(Vertex3f & direction) {
  origin.moveTo(0, 0, 0);
  this->direction = direction;
  hitted_face = -1;
  hitted_obj = NULL;
}

Ray::Ray(Vertex3f & origin, Vertex3f & direction) {
  this->origin = origin;
  this->direction = direction;
  hitted_face = -1;
  hitted_obj = NULL;
}

Ray::Ray(float d_x, float d_y, float d_z) {
  origin.moveTo(0, 0, 0);
  direction.moveTo(d_x, d_y, d_z);
  hitted_face = -1;
  hitted_obj = NULL;
}

Ray::Ray(float o_x, float o_y, float o_z, float d_x, float d_y, float d_z) {
  origin.moveTo(o_x, o_y, o_z);
  direction.moveTo(d_x, d_y, d_z);
  hitted_face = -1;
  hitted_obj = NULL;
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

void Ray::setLength(float t) {
  if(t < this->length && t > 1e-4) {
    this->length = t;
  }
}

bool Ray::updateLength(float t) {
  if(t <= this->length && t > 1e-4 && t < FLT_MAX) {
    this->length = t;
    return true;
  }
  return false;
}


float Ray::getLength() {
  return this->length;
}

void Ray::setMaxLength(float t) {
  this->max_length = t;
}

float Ray::getMaxLength() {
  return this->max_length;
}

void Ray::setHittedObject(Object* obj) {
  this->hitted_obj = obj;
}

Object* Ray::getHittedObject() {
  return this->hitted_obj;
}

void Ray::setHittedFace(int face) {
  this->hitted_face = face;
}

int Ray::getHittedFace() {
  return this->hitted_face;
}

void Ray::setUV(float u, float v) {
  this->u = u;
  this->v = v;
}

void Ray::getUV(float &u, float &v) {
  u = this->u;
  v = this->v;
}

void Ray::setNormal(Vertex3f & n) {
  this->n = n;
}

Vertex3f& Ray::getNormal() {
  return this->n;
}

void Ray::print() {
  std::cout << "Origin = ";
  origin.print();
  std::cout << "Direction = ";
  direction.print();
}
