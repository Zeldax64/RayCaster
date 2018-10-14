#pragma once

#include <iostream>
#include <IL/il.h>

#include "core/color/Color.h"

bool loadImage(const char *filename, Color * & buffer);
int getImageWidth();
int getImageHeight();
