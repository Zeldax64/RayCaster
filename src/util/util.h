#pragma once

#include <iostream>
#include <stdint.h>
#include <GL/glut.h>
#include "core/color/Color.h"

void display(void);
void updateScreen(Color* buffer, uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT);
void drawPixel(int x, int y);
void setUpOpenGL(uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT);
int mainGL(int argc, char **argv, uint32_t screen_width, uint32_t screen_height, Color* buff);
