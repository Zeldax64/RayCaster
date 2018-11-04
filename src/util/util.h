#pragma once

#include <iostream>

#include <stdint.h>
#include <GL/glut.h>

#include "core/math/Vertex3f.h"
#include "core/math/TMatrix.h"
#include "core/color/Color.h"
#include "core/renderer/RayCasting.h"
#include "core/scenery/Scenery.h"
#include "core/camera/Camera.h"

void display(void);
void updateScreen(Color* buffer, uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT);
void drawPixel(int x, int y);
void setUpOpenGL(uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT);
void keyboardDown(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void keyboardSpecial(int key, int x, int y);
void rotateCamera(float dir);
void rotateObject();
int mainGL(int argc, char **argv, RayCasting & render);
