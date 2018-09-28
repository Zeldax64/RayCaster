#pragma once

#include <iostream>
#include <stdint.h>
#include "core/scenery/Scenery.h"
#include "core/color/Color.h"
#include "core/camera/Camera.h"

class RayCasting
{

  uint32_t x_width;
  uint32_t y_width;
  Scenery* scn;
  Color* buff; //Create buffer class?
  Camera* cam;

  // Window parameters
  float d;  // Camera distance from the window
  float H;
  float W;
  float dx;
  float dy;
public:
  RayCasting(uint32_t x_width, uint32_t y_width);
  ~RayCasting();

  // Method to render scene
  void render();

  // Scenery methods
  void setScenery(Scenery * scn);
  void setCamera(Camera * cam);

  Scenery* getScenery();
  Camera* getCamera();

private:
  Vertex3f genRay(int pix_x, int pix_y);
};
