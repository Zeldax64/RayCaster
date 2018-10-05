/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/
#pragma once
#include <math.h>

#include "core/math/Vertex3f.h"
#include "core/objects/geometric/GSphere.h"

// Geometrical Objects
float hitSphere(Vertex3f & ray, GSphere* sphere); // Can be used with a sphere cluster
float hitSphereRayLength(Vertex3f & ray, GSphere* sphere);

// Triangle
