#pragma once

#include <list>
#include "core/objects/Object.h"
#include "core/math/TMatrix.h"
#include "core/camera/Camera.h"

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
// Camera methods
  void setCamPos(Vertex3f position);
  void setCamLookAt(Vertex3f position);
  void setCamAViewUp(Vertex3f position);
  void calcCamCoord();

  void worldToCamTransform();
  void camToWorldTransform();

  TMatrix getWorldToCamTransform();
  TMatrix getCamToWorldTransform();

};
