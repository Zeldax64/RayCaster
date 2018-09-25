#pragma once

#include <list>
#include "core/objects/Object.h"
#include "core/math/TMatrix.h"

class Scenery
{
  std::list<Object*> objs;

public:
  Scenery();
  ~Scenery();

// Object methods
  void addObj(Object* obj);
//  void delObj(Object obj);
//  void findObj(Object obj);
                                                                                                                                                                                                                Object* getObj(int i);
  void applyTransform(Object* obj, const TMatrix & matrix);

};
