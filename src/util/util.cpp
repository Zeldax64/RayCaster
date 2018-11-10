#include "util/util.h"

static RayCasting* rdr;
static Scenery* scn;
static Camera* cam;
static Color* buffer;
static uint32_t SCREEN_WIDTH;
static uint32_t SCREEN_HEIGHT;
static bool rotatex = false;
static bool rotatey = false;
static bool rotatez = false;

bool mouse_debug = false;

/* Buffer Debug functions */
void setPixel(uint32_t x, uint32_t y, float r, float g, float b) {
  buffer[y * SCREEN_WIDTH + x].setColor(r, g, b);
}

void drawHLine(uint32_t x, uint32_t y, uint32_t l){

  if ((x>=0) && (x<SCREEN_WIDTH) && (y>=0) && (y<SCREEN_HEIGHT)){
    for (uint32_t cx=0; cx<l; cx++){
      buffer[y * SCREEN_WIDTH + cx + x].setColor(1.0, 0, 0);
    }
  }
}

void drawVLine(uint32_t x, uint32_t y, uint32_t l){

  if ((x>=0) && (x<SCREEN_WIDTH) && (y>=0) && (y<SCREEN_HEIGHT)){
    for (uint32_t cy=0; cy<= l; cy++){
      setPixel(x, y+cy, 1.0, 0.0, 0.0);
    }
  }
}

/*------------------------*/
void renderBuffer() {
  std::cout << "render()\n";
  if(rotatex || rotatey || rotatez) {
    rotateObject();
  }

  rdr->render();
  buffer = rdr->getBuffer();
  glutPostRedisplay();
}

void display(void) {
  std::cout << "Display()\n";
  updateScreen(buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
  glutSwapBuffers();
  if(rotatex || rotatey || rotatez) {
    rotateObject();
  }
}

void drawPixel(int x, int y) {
	glBegin(GL_POINTS);
    glVertex2i(x, y);
	glEnd();
}

// Draw screen
void updateScreen(Color* buffer, uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT) {
	for(uint32_t y = 0; y < SCREEN_HEIGHT; ++y){
		for(uint32_t x = 0; x < SCREEN_WIDTH; ++x){
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
  std::cout << "keyboardSpecial()\n";
  switch(key) {
    case GLUT_KEY_LEFT:
      rotateCamera(-1.0);
      renderBuffer();
    break;
    case GLUT_KEY_RIGHT:
      rotateCamera(1.0);
      renderBuffer();
    break;
    case GLUT_KEY_F1:
      rotatex = (!rotatex);
      renderBuffer();
    break;
    case GLUT_KEY_F2:
      rotatey = (!rotatey);
      renderBuffer();
    break;
    case GLUT_KEY_F3:
      rotatez = (!rotatez);
      renderBuffer();
    break;

  }

}

void mouse(int button,int state,int x,int y) {
  Ray ray;
  float l, c, t;
  bool shadow;
  std::cout << "--- mouse() --- \n";

  switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state==GLUT_DOWN) {
			std::cout << "Mouse X: " << x << " Y: " << y << "\n";
      mouse_debug = true;
      //x = 269; y = 187;

      l = (1.0/2) - (1.0/SCREEN_HEIGHT)/2 - y * (1.0/SCREEN_HEIGHT);
      c = -(1.0/2) + (1.0/SCREEN_WIDTH)/2 + x * (1.0/SCREEN_WIDTH);

      Vertex3f vector = Vertex3f(c, l, -1.0);
      vector = vector.unit();

      ray.setDirection(vector);
      t = scn->castRay(ray);
      buffer[y*SCREEN_WIDTH+x].print();

      std::cout << "T = " << t << "\n";

      Vertex3f ray_dir = ray.getDirection();
      Vertex3f ray_org = ray.getOrigin();
      Vertex3f hit_point = ray_dir * t + ray_org;

      shadow = rdr->calcShadow(scn->getLight(0), hit_point);
      std::cout << "Shadow: " << shadow << "\n";
      std::cout << "ray: "; ray.print();
      mouse_debug = false;
    }
		break;
	case GLUT_MIDDLE_BUTTON:
		if(state==GLUT_DOWN) {
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state==GLUT_DOWN) {

    }
		break;
	default:
		break;
	}
  std::cout << "--- mouse() --- \n";

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
  renderBuffer();
}

void rotateObject() {
  float theta = 10.0;
  TMatrix X, Y, Z, RES;

  if(rotatex)
    X.rotateX(theta);
  if(rotatey)
    Y.rotateY(theta);
  if(rotatez)
    Z.rotateZ(theta);

  RES = X*Y*Z;

  Object* obj = scn->getObj(0);
  scn->camToWorldTransform();
  obj->applyTransform(RES);
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
  glutMouseFunc(mouse);
  renderBuffer();
  glutMainLoop();
  return 0;
}
