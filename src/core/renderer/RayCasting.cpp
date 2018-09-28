#include "core/renderer/RayCasting.h"

RayCasting::RayCasting(uint32_t x_width, uint32_t y_width) {
  buff = new Color[x_width * y_width];
  this->x_width = x_width;
  this->y_width = y_width;
  this->H = 10.0;
  this->W = 10.0;
  this->dx = this->W / this->x_width;
  this->dy = this->H / this->y_width;
}


RayCasting::~RayCasting() {
  //delete[] scn;
  delete[] buff;
}

void RayCasting::render() {
  float x_coord, y_coord;

  for(uint32_t l = 0; l < y_width; l++) {
    float y = -(H/2) - dy/2 - l * dy;
    for(uint32_t c = 0; c < x_width; c++) {
      float x = -(W/2) + dx/2 + c * dx;
      Vertex3f ray = Vertex3f(c, l, -d);
      // Check if this is correct or not
      buff[l*x_width + c] = scn->hitRay(ray);
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

// TODO: Check whether this function is useless
Vertex3f RayCasting::genRay(int pix_x, int pix_y) {
}
