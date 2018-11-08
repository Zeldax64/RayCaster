/*
  Based on the code from: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*/

#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include "core/math/Vertex3f.h"
#include "core/math/Face3f.h"

bool loadOBJ (
  const char* path,
  std::vector <Vertex3f> * out_vertices,
  std::vector <Face3f> * out_faces
);
