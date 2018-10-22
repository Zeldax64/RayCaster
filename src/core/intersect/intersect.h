/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/
#pragma once

#include <list>

#include <math.h>
#include <float.h>

#include "core/math/Vertex3f.h"
#include "core/math/Ray.h"
#include "core/objects/geometric/GSphere.h"

// List of objects
float hitObjectList(std::list<Object*> & objs, Ray & ray, Material * & mat, Vertex3f & n);
float hitFirstObjectList(std::list<Object*> & objs, Ray & ray);
// Geometrical Objects
float hitSphere(Ray & ray, GSphere* sphere); // Can be used with a sphere cluster
float hitSphereRayLength(Ray & ray, GSphere* sphere);

// Triangle
float hitTriangle(Ray & ray, Vertex3f & v0, Vertex3f & v1, Vertex3f & v2, Vertex3f & ret_n);
