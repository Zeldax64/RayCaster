#pragma once

#include <list>
#include <iostream>

#include <float.h>
#include <stdint.h>

#include "core/objects/Object.h"
#include "core/math/TMatrix.h"
#include "core/camera/Camera.h"
#include "core/color/Color.h"
#include "core/light/Light.h"
#include "core/light/LPoint.h"
#include "core/material/Material.h"
#include "core/math/Ray.h"

#include "core/intersect/intersect.h"

class Scenery
{
  std::list<Light*> lights;

  Camera cam;
  bool is_coord_world;
  Color k_amb;

public:
  std::list<Object*> objs;

  Scenery();
  ~Scenery();

/*----- Object methods -----*/
  void addObj(Object* obj);
//  void delObj(Object obj);
//  void findObj(Object obj);
  Object* getObj(uint32_t i);
  void applyTransformAll(const TMatrix & matrix);

/*----- Ray Intersection -----*/
  float hitRay(Ray & ray, Material & mat, Vertex3f & n);
  float lookShadow(Ray & ray);

/*----- Light sources methods -----*/
  void addLight(Light* source);
  Light* getLight(uint32_t i);
  std::list<Light*>* getLights();
  void setAmb(float r, float g, float b);
  Color* getAmb();
/*----- Camera methods -----*/
  void setCamPos(Vertex3f position);
  void setCamLookAt(Vertex3f position);
  void setCamAViewUp(Vertex3f position);
  void calcCamCoord();

  Camera* getCam();

/*----- Coordinates transformations -----*/
  bool isCoordWorld();

  void worldToCamTransform();
  void camToWorldTransform();

  TMatrix getWorldToCamTransform();
  TMatrix getCamToWorldTransform();

};
