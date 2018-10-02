#include "util/util.h"

static Color* buffer;
static uint32_t SCREEN_WIDTH;
static uint32_t SCREEN_HEIGHT;

void display(void) {
  updateScreen(buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
  glutSwapBuffers();
}


void drawPixel(int x, int y) {
	glBegin(GL_POINTS);
    glVertex2i(x, y);
	glEnd();
}

// Draw screen
/*
  TODO: There might be a bug here!
*/
void updateScreen(Color* buffer, uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT) {
	for(int y = 0; y < SCREEN_HEIGHT; ++y){
		for(int x = 0; x < SCREEN_WIDTH; ++x){
        // Get color
      float r = buffer[y * SCREEN_WIDTH + x].getRed();
      float g = buffer[y * SCREEN_WIDTH + x].getGreen();
      float b = buffer[y * SCREEN_WIDTH + x].getBlue();
      // Debug if
      if(r == 1.0 && g == 0.0) {
        std::cout << "[" << x << ":" << y << "] = r" << r << "\n";
        glColor3f(r, g, b);
      }
      else{
        glColor3f(0.0, 0.0, 0.0);
      }
      drawPixel(x, y);
		}
	}
}

void setUpOpenGL(uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("SiGAPI");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0);

	glMatrixMode(GL_MODELVIEW);
}

int mainGL(int argc, char **argv, uint32_t screen_width, uint32_t screen_height, Color* buff) {
  glutInit(&argc, argv);
  buffer = buff;
  SCREEN_WIDTH = screen_width;
  SCREEN_HEIGHT = screen_height;
  setUpOpenGL(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
