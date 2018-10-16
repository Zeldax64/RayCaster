/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/
#pragma once

#include <list>

#include <math.h>
#include <float.h>

#include "core/math/Vertex3f.h"
#include "core/objects/geometric/GSphere.h"

// List of objects
float hitObjectList(std::list<Object*> & objs, Vertex3f ray, Material * & mat, Vertex3f & n);

// Geometrical Objects
float hitSphere(Vertex3f & ray, GSphere* sphere); // Can be used with a sphere cluster
float hitSphereRayLength(Vertex3f & ray, GSphere* sphere);

// Triangle
float hitTriangle(Vertex3f ray, Vertex3f & v0, Vertex3f & v1, Vertex3f & v2, Vertex3f & ret_n);
