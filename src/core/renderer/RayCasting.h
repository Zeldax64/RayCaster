#pragma once

#include <iostream>
#include <stdint.h>
#include <math.h>
#include "core/scenery/Scenery.h"
#include "core/color/Color.h"
#include "core/camera/Camera.h"
#include "core/material/Material.h"

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

  Color* getBuffer();

private:
  void calcIllumination(Color * buffer, float t, Material & mat, Vertex3f & ray, Vertex3f & n);
};
