#pragma once

#include <list>
#include <iostream>

#include <float.h>

#include "core/objects/Object.h"
#include "core/math/TMatrix.h"
#include "core/camera/Camera.h"
#include "core/color/Color.h"
#include "core/light/Light.h"

class Scenery
{
  std::list<Object*> objs;
  std::list<Light*> lights;

  Camera cam;
public:
  Scenery();
  ~Scenery();

/*----- Object methods -----*/
  void addObj(Object* obj);
//  void delObj(Object obj);
//  void findObj(Object obj);
  Object* getObj(int i);
  void applyTransformAll(const TMatrix & matrix);

/*----- Ray Intersection -----*/
  Color hitRay(Vertex3f ray);

/*----- Light sources methods -----*/
  void addLight(Light* source);
  Light* getLight(int i);

/*----- Camera methods -----*/
  void setCamPos(Vertex3f position);
  void setCamLookAt(Vertex3f position);
  void setCamAViewUp(Vertex3f position);
  void calcCamCoord();

  Camera* getCam();

/*----- Coordinates transformations -----*/
  void worldToCamTransform();
  void camToWorldTransform();

  TMatrix getWorldToCamTransform();
  TMatrix getCamToWorldTransform();

};
