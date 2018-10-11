#include "core/renderer/RayCasting.h"

RayCasting::RayCasting(uint32_t x_width, uint32_t y_width) {
  buff = new Color[x_width * y_width];
  this->x_width = x_width;
  this->y_width = y_width;
  this->H = 1.0;
  this->W = 1.0;
  this->dx = this->W / this->x_width;
  this->dy = this->H / this->y_width;
  this->d = 1.0;
}


RayCasting::~RayCasting() {
  //delete[] scn;
  delete[] buff;
}

void RayCasting::render() {
  float x_coord, y_coord;
  scn->worldToCamTransform();

  for(uint32_t l = 0; l < y_width; l++) {
    float y = (H/2) - dy/2 - l * dy;
    for(uint32_t c = 0; c < x_width; c++) {
      float x = -(W/2) + dx/2 + c * dx;
      Vertex3f ray = Vertex3f(x, y, -d);
      Vertex3f n;
      Material mat;
      float t;
      t = scn->hitRay(ray, mat, n);

      if(t >= 1.0 && t < FLT_MAX) {
        calcIllumination(&buff[l*x_width+c],
                         t,
                         mat,
                         ray,
                         n
                       );
      }
      else {
        buff[l*x_width+c].setColor(0.0, 0.0, 0.0);
      }
    }
  }
}

void RayCasting::setScenery(Scenery * scn) {
  this->scn = scn;
}

void RayCasting::setCamera(Camera * cam) {
  this->cam = cam;
}

Scenery* RayCasting::getScenery() {
  return scn;
}

Camera* RayCasting::getCamera() {
  return cam;
}

Color* RayCasting::getBuffer() {
  return buff;
}


// Private methods
void RayCasting::calcIllumination(Color * buffer, float t, Material & mat, Vertex3f & ray, Vertex3f & n) {
  // Copy from here on
  Light* src = scn->getLight(0);
  Color* src_int = src->getSource();
  Color* col_amb = src->getAmb();

  // Handling vectors
  Vertex3f hit_point = ray * t;
  Vertex3f l = *(src->getPosition()) - hit_point;
  l = l.unit();
  Vertex3f v = (-hit_point).unit();

  // Ambient illumination
  Color* kamb = mat.getAmb();
  Color I_amb = (*col_amb) * (*kamb);

  // Diffuse illumination
  float cos_theta = n.dotProduct(l);
  Color I_dif;
  if(cos_theta >= 0.0) {
    Color* kdif = mat.getDif();
    I_dif =  (*src_int) * (*kdif) * cos_theta;
  }
  else {
    I_dif = (*src_int) * 0.0;
  }
  // Specular illumination
  Color* k_esp = mat.getEsp();
  Vertex3f r = n*2*(l.dotProduct(n))*n-l;
  cos_theta = r.dotProduct(v);
  Color I_esp = (*src_int) * (*k_esp) * cos_theta;

  // Result
  *buffer = I_amb + I_dif + I_esp;
}
