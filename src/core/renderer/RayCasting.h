#pragma once

#include <iostream>
#include <list>

#include <stdint.h>
#include <math.h>
#include <float.h>

#include "core/math/Ray.h"
#include "core/scenery/Scenery.h"
#include "core/color/Color.h"
#include "core/camera/Camera.h"
#include "core/material/Material.h"
#include "util/background.h"

class RayCasting
{

  uint32_t width;
  uint32_t height;
  Scenery* scn;
  Camera* cam;
  Color* buff; //Create buffer class?
  Color* bg_buff;   // Background buffer; TODO: Maybe create a Image class?
  bool bg;
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
  bool loadBG(const char* filename);

  Scenery* getScenery();
  Camera* getCamera();

  uint32_t getWidth();
  uint32_t getHeight();

  Color* getBuffer();
  Color* getBG();

  void calcIllumination(Color * buffer, Ray & ray);
  bool calcShadow(Light* src, Vertex3f intersection);
};
