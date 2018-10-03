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

// It looks unnecessary
//void Scenery::applyTransform(Object* obj, const TMatrix & matrix) {}

void Scenery::applyTransformAll(const TMatrix & matrix) {
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    (*it)->applyTransform(matrix);
  }
}

/*----- Ray Intersection -----*/
Color Scenery::hitRay(Vertex3f ray) {
  Color col(1.0, 1.0, 1.0);

  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    if((*it)->hitObject(ray, col)) {
      //std::cout << "Scenery.cpp -> Object hitted! ";
      //ray.print();
      return col;
    }
  }
  return col;
}

/*----- Camera Methods -----*/
void Scenery::setCamPos(Vertex3f position) { cam.setPosition(position); }
void Scenery::setCamLookAt(Vertex3f position) { cam.setLookAt(position); }
void Scenery::setCamAViewUp(Vertex3f position) { cam.setAViewUp(position); }
void Scenery::calcCamCoord() { cam.calcCoordSystemBasis(); }

// TODO: finish this method
void Scenery::worldToCamTransform() {
  TMatrix transform = getWorldToCamTransform();

  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    (*it)->applyTransform(transform);
  }
}

// TODO: finish this method
void Scenery::camToWorldTransform() {
  TMatrix transform = getCamToWorldTransform();

  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    (*it)->applyTransform(transform);
  }
}

TMatrix Scenery::getWorldToCamTransform() {
  TMatrix transform;
  Vertex3f i = cam.getI();
  Vertex3f j = cam.getJ();
  Vertex3f k = cam.getK();
  Vertex3f pos = cam.getPosition();

  transform.worldBasisToCoord(i, j, k, pos);
  return transform;
}

TMatrix Scenery::getCamToWorldTransform() {
  TMatrix transform;
  Vertex3f i = cam.getI();
  Vertex3f j = cam.getJ();
  Vertex3f k = cam.getK();
  Vertex3f pos = cam.getPosition();

  transform.coordBasisToWorld(i, j, k, pos);

  return transform;
}
