#include "core/scenery/Scenery.h"

Scenery::Scenery() {
  is_coord_world = true;
}

Scenery::~Scenery() {
}

/*----- Object methods -----*/
void Scenery::addObj(Object* obj) {
  objs.push_back(obj);
}
//  void delObj(Object obj);
//  void findObj(Object obj);

// Return as pointer to the object
Object* Scenery::getObj(uint32_t i) {
  if(i >= objs.size())
    return NULL;

  std::list<Object*>::iterator it = objs.begin();
  std::advance(it, i);
  return *it;
}

void Scenery::applyTransformAll(const TMatrix & matrix) {
  std::list<Object*>::iterator it_objs;
  for(it_objs = objs.begin(); it_objs != objs.end(); ++it_objs){
    (*it_objs)->applyTransform(matrix);
  }

  std::list<Light*>::iterator it_lights;
  for(it_lights = lights.begin(); it_lights != lights.end(); ++it_lights){
    (*it_lights)->applyTransform(matrix);
  }
}

/*----- Ray Intersection -----*/
// TODO: handle this code in a separete function. this will be useful
// in models which cointain more than one object.
// Object hitObject must also return a material or a reference to the
// hitted object.
float Scenery::hitRay(Ray & ray, Material & mat, Vertex3f & n) {
  Material* first_mat;
  float best_t = hitObjectList(objs, ray, first_mat, n);

  if(best_t < FLT_MAX) {
    mat = *first_mat;
  }

  return best_t;
}

// TODO: Beware of the shadow acme problem and check epsilon
float Scenery::lookShadow(Ray & ray) {
  float t = hitFirstObjectList(objs, ray);
  return t;
}

/*----- Light sources methods -----*/
void Scenery::addLight(Light* source) {
  lights.push_back(source);
}

Light* Scenery::getLight(uint32_t i) {
  if(i >= objs.size())
    return NULL;

  std::list<Light*>::iterator it = lights.begin();
  std::advance(it, i);
  return *it;
}

std::list<Light*>* Scenery::getLights() { return &lights; }

/*----- Camera Methods -----*/
void Scenery::setCamPos(Vertex3f position) { cam.setPosition(position); }
void Scenery::setCamLookAt(Vertex3f position) { cam.setLookAt(position); }
void Scenery::setCamAViewUp(Vertex3f position) { cam.setAViewUp(position); }
void Scenery::calcCamCoord() { cam.calcCoordSystemBasis(); }

Camera* Scenery::getCam() { return &cam; }

/*----- Coordinates transformations -----*/
bool Scenery::isCoordWorld() {
  return is_coord_world;
}

void Scenery::worldToCamTransform() {
  if(this->isCoordWorld()) {
    std::cout << "worldToCamTransform()\n";
    TMatrix transform = getWorldToCamTransform();
    this->applyTransformAll(transform);
    is_coord_world = false;
  }
}

void Scenery::camToWorldTransform() {
  if(!this->isCoordWorld()) {
    std::cout << "camToWorldTransform()\n";
    TMatrix transform = getCamToWorldTransform();
    this->applyTransformAll(transform);
    is_coord_world = true;
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
