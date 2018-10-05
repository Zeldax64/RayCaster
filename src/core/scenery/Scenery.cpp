#include "core/scenery/Scenery.h"

Scenery::Scenery() {}
Scenery::~Scenery() {}

/*----- Object methods -----*/
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

void Scenery::applyTransformAll(const TMatrix & matrix) {
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    (*it)->applyTransform(matrix);
  }
}

/*----- Ray Intersection -----*/
// TODO: Iterate through light sources case a light source is an object?
Color Scenery::hitRay(Vertex3f ray) {
  Color col(0.0, 0.0, 0.0); // Background color
  Color* first_col;
  float best_t = FLT_MAX;
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    if((*it)->hitObject(ray, col) <= best_t) {
      Material* mat = (*it)->getMaterial();
      first_col = mat->getColor();
    }
  }
  
  if(best_t < FLT_MAX) {
    col.setColor((*first_col).getRed(),
                 (*first_col).getGreen(),
                 (*first_col).getBlue()
    );
  }
  return col;
}

/*----- Light sources methods -----*/
void Scenery::addLight(Light* source) {
  lights.push_back(source);
}

Light* Scenery::getLight(int i) {
  if(i >= objs.size())
    return NULL;

  std::list<Light*>::iterator it = lights.begin();
  std::advance(it, i);
  return *it;
}

/*----- Camera Methods -----*/
void Scenery::setCamPos(Vertex3f position) { cam.setPosition(position); }
void Scenery::setCamLookAt(Vertex3f position) { cam.setLookAt(position); }
void Scenery::setCamAViewUp(Vertex3f position) { cam.setAViewUp(position); }
void Scenery::calcCamCoord() { cam.calcCoordSystemBasis(); }

Camera* Scenery::getCam() { return &cam; }

/*----- Coordinates transformations -----*/
// TODO: finish this method -> Add transf. to light souces
void Scenery::worldToCamTransform() {
  TMatrix transform = getWorldToCamTransform();

  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    (*it)->applyTransform(transform);
  }
}

// TODO: finish this method -> Add transf. to light souces
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
