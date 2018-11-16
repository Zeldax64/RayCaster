/*
  This class can be improved to solve different problems in the program
*/

#pragma once

#include <iostream>

#include <float.h>

#include "core/objects/Object.h"
#include "core/math/Vertex3f.h"

class Object;

class Ray
{
  Vertex3f origin;
  Vertex3f direction;
  float length = FLT_MAX;
  float max_length = FLT_MAX;

  Object* hitted_obj;
  int hitted_face;
  float u, v;

public:
  Ray();
  Ray(Vertex3f & direction);
  Ray(Vertex3f & origin, Vertex3f & direction);
  Ray(float d_x, float d_y, float d_z);
  Ray(float d_x, float d_y, float d_z, float o_x, float o_y, float o_z);
  ~Ray();

  void setOrigin(float o_x, float o_y, float o_z);
  void setDirection(float d_x, float d_y, float d_z);
  void setOrigin(Vertex3f & O);
  void setDirection(Vertex3f & dir);

  Vertex3f& getOrigin();
  Vertex3f& getDirection();

  void setLength(float t);
  bool updateLength(float t);
  float getLength();

  void setMaxLength(float t);
  float getMaxLength();

  void setHittedObject(Object* obj);
  Object* getHittedObject();

  void setHittedFace(int hitted_face);
  int getHittedFace();

  void setUV(float u, float v);
  void getUV(float &u, float &v);

  void print();
};
