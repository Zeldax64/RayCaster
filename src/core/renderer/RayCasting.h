#pragma once

#include "core/scenery/Scenery.h"

class RayCasting
{
  Scenery* scn;

public:
  RayCasting();
  ~RayCasting();

  // Sets camera in scenery
  void setCam();

};
