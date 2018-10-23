#include "util/util.h"

static RayCasting* rdr;
static Scenery* scn;
static Camera* cam;
static Color* buffer;
static uint32_t SCREEN_WIDTH;
static uint32_t SCREEN_HEIGHT;

/* Buffer Debug functions */
void setPixel(uint32_t x, uint32_t y, float r, float g, float b) {
  buffer[y * SCREEN_WIDTH + x].setColor(r, g, b);
}

void drawHLine(int x, int y, int l){

  if ((x>=0) && (x<SCREEN_WIDTH) && (y>=0) && (y<SCREEN_HEIGHT)){
    for (int cx=0; cx<l; cx++){
      buffer[y * SCREEN_WIDTH + cx + x].setColor(1.0, 0, 0);
    }
  }
}

void drawVLine(int x, int y, int l){

  if ((x>=0) && (x<SCREEN_WIDTH) && (y>=0) && (y<SCREEN_HEIGHT)){
    for (int cy=0; cy<= l; cy++){
      setPixel(x, y+cy, 1.0, 0.0, 0.0);
    }
  }
}

/*------------------------*/

void display(void) {
  std::cout << "display()\n";
  rdr->render();
  buffer = rdr->getBuffer();
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
      glColor3f(r, g, b);
      drawPixel(x, y);
		}
	}
}

void keyboardDown(unsigned char key, int x, int y) {
  if(key == 27)    // esc
    exit(0);


}

void keyboardUp(unsigned char key, int x, int y) {}

void keyboardSpecial(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT:
      rotateCamera(-1.0);
    break;
    case GLUT_KEY_RIGHT:
      rotateCamera(1.0);
    break;
  }
}

void rotateCamera(float dir) {
  float theta = 10.0;
  theta = theta * dir;

  TMatrix rotatey;
  rotatey.rotateY(theta);

  Vertex3f pos = cam->getPosition();
/*
  std::cout << "rotateCamera()";
  std::cout << "CamPos (old): "; pos.print();
  std::cout << "rotateCamera";
*/
  pos.applyTransform(rotatey);
  cam->setPosition(pos);
//  std::cout << "CamPos (new): "; (cam->getPosition()).print();
  scn->camToWorldTransform();
  scn->calcCamCoord();
  cam->print();
  glutPostRedisplay();
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

int mainGL(int argc, char **argv, RayCasting & render) {
  glutInit(&argc, argv);
  buffer = render.getBuffer();
  rdr = &render;
  scn = render.getScenery();
  cam = scn->getCam();
  SCREEN_WIDTH = render.getWidth();
  SCREEN_HEIGHT = render.getHeight();
  setUpOpenGL(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardDown);
  glutSpecialFunc(keyboardSpecial);
  glutMainLoop();
  return 0;
}
