#include "core/scenery/Scenery.h"

Scenery::Scenery() {}
Scenery::~Scenery() {}

// Object methods
void Scenery::addObj(Object* obj) {
  objs.push_back(obj);
}
//  void delObj(Object obj);
//  void findObj(Object obj);

// Return as pointer to the object
Object* Scenery::getObj(int i) {
  if(i >= objs.size())
    return NULL;

  std::list<Object*>::iterator it = objs.begin();
  std::advance(it, i);
  return *it;
}

void Scenery::applyTransform(Object* obj, const TMatrix & matrix) {

}
