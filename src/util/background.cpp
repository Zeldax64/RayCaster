// TODO: maybe move the contents of this file to objloader
// to have just one file read source in the entire project
#include "util/background.h"

bool loadImage(const char *filename, Color * & buffer) {
   ILuint    image;
   ILboolean success;
   // TODO: test background again
   ilInit();
   ilEnable(IL_ORIGIN_SET);
   ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

   ilGenImages(1, &image);
   ilBindImage(image);

   success = ilLoadImage(filename);
   if (success) {
       success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
       if (!success) {
          return false;
       }
   }
   else {
       return false;
   }

	 int width  = ilGetInteger(IL_IMAGE_WIDTH);
	 int height = ilGetInteger(IL_IMAGE_HEIGHT);

   buffer = new Color[width*height];
   ILubyte * bytes = ilGetData();
   for (int i = 0; i < height; i++) {
     for (int j = 0; j < width; j++) {
       float r = bytes[(i*width + j)*3 + 0]/255.0;
       float g = bytes[(i*width + j)*3 + 1]/255.0;
       float b = bytes[(i*width + j)*3 + 2]/255.0;

       buffer[i*width+j].setColor(r, g, b);
     }
   }

   return true;
}

int getImageWidth() { return ilGetInteger(IL_IMAGE_WIDTH); }

int getImageHeight() { return ilGetInteger(IL_IMAGE_HEIGHT); }
