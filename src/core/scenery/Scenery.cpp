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
// TODO: Iterate through light sources case a light source is an object?
// Returning color of the closest object or background
Color Scenery::hitRay(Vertex3f ray) {
  Color col(0.0, 0.0, 0.0); // Background color
  Vertex3f normal; // Normal of the hitted face
  Vertex3f best_normal; // Normal of the hitted face
  Material* first_mat;
  float best_t = FLT_MAX;
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    float t = (*it)->hitObject(ray, normal);
    if(t <= best_t && t >= 1.0) {
      best_t = t;
      best_normal = normal;
      first_mat = (*it)->getMaterial();
    }
  }

// This code may be moved to RayCasting class
  if(best_t < FLT_MAX) {
    Light* src = getLight(0);
    Color* src_int = src->getSource();
    Color* col_amb = src->getAmb();

    // Handling vectors
    normal = best_normal.unit();
    Vertex3f hit_point = ray * best_t;
    Vertex3f l = *(src->getPosition()) - hit_point;
    l = l.unit();
    Vertex3f v = (-hit_point).unit();

    // Ambient illumination
    Color* kamb = first_mat->getAmb();
    Color I_amb = (*col_amb) * (*kamb);

    // Diffuse illumination
    float cos_theta = normal.dotProduct(l);
    Color* kdif = first_mat->getDif();
    Color I_dif =  (*src_int) * (*kdif) * cos_theta;

    // Specular illumination
    Color* k_esp = first_mat->getEsp();
    Vertex3f r = normal*2*(l.dotProduct(normal))*normal-l;
    cos_theta = r.dotProduct(v);
    Color I_esp = (*src_int) * (*k_esp) * cos_theta;

    // Result
    col = I_amb + I_dif + I_esp;
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

  /*
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it){
    (*it)->applyTransform(transform);
  }
  */
  this->applyTransformAll(transform);
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
