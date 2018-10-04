#pragma once

#include <list>
#include <iostream>
#include "core/objects/Object.h"
#include "core/math/TMatrix.h"
#include "core/camera/Camera.h"
#include "core/color/Color.h"

class Scenery
{
  std::list<Object*> objs;
  Camera cam;
public:
  Scenery();
  ~Scenery();

// Object methods
  void addObj(Object* obj);
//  void delObj(Object obj);
//  void findObj(Object obj);
                                                                                                                                                                                                                Object* getObj(int i);
//  void applyTransform(Object* obj, const TMatrix & matrix); // It looks unnecessary
  void applyTransformAll(const TMatrix & matrix);

// Ray intersection verification
  Color hitRay(Vertex3f ray);

// Camera methods
  void setCamPos(Vertex3f position);
  void setCamLookAt(Vertex3f position);
  void setCamAViewUp(Vertex3f position);
  void calcCamCoord();

  Camera* getCam();

  void worldToCamTransform();
  void camToWorldTransform();

  TMatrix getWorldToCamTransform();
  TMatrix getCamToWorldTransform();

};
