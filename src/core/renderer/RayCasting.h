#pragma once

#include "core/scenery/Scenery.h"

class RayCasting
{
  Scenery* scn;
// Buffer* buff; Create buffer class?

public:
  RayCasting();
  ~RayCasting();

  // Method to render scene
  void render();
  // Sets camera in scenery
  void setCam();

  // Scenery methods
  void setScenery(Scenery * scn);

};
