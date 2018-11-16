/*
  This file cointains intersection test functions which will be used in
  object classes to handle ray intersection.
*/
#pragma once

#include <list>

#include <math.h>
#include <float.h>
#include <stdint.h>

#include "core/math/Vertex3f.h"
#include "core/math/Face3f.h"
#include "core/math/Ray.h"
#include "core/objects/Object.h"
#include "core/objects/geometric/GSphere.h"

// List of objects
float hitObjectList(std::list<Object*> & objs, Ray & ray, Material * & mat, Vertex3f & n);
float hitFirstObjectList(std::list<Object*> & objs, Ray & ray);
// Geometrical Objects
float hitSphere(Ray & ray, GSphere* sphere); // Can be used with a sphere cluster
float hitSphereRayLength(Ray & ray, GSphere* sphere);

// Triangle
float hitTriangle(Ray & ray, Vertex3f & v0, Vertex3f & v1, Vertex3f & v2, float & out_u, float & out_v);
float hitTriangles(Ray & ray, Object * obj, Vertex3f * vertices, Face3f * faces, uint32_t faces_num, Vertex3f & ret_n, Material * & ret_mat);
