#include "app/objects/SnowMan.h"

SnowMan::SnowMan(float x, float y, float z) {
  float dx = x;
	float dy = y;
	float dz = z;

  snow = new Material(1.0, 1.0, 1.0,
                      0.7, 0.7, 0.7,
                      1.0, 1.0, 1.0);

  rock = new Material(0.0, 0.0, 0.0,
                      0.5, 0.5, 0.5,
                      0.5, 0.5, 0.5);

	GSphere* body = new GSphere(Vertex3f(0.0+dx, 0.0+dy, 0.0+dz),
																3.0,
																*snow);

	// Head
	GSphere* head = new GSphere(Vertex3f(0.0+dx, 4.0+dy, 0.0+dz),
																1.0,
																*snow);

	// Left eye
	GSphere* left_eye = new GSphere(Vertex3f(1.0+dx, 4.25+dy, 0.45+dz),
																	0.15,
																	*rock
																);

	// Right eye
	GSphere* right_eye = new GSphere(Vertex3f(1.0+dx, 4.25+dy, -0.45+dz),
																	0.15,
																	*rock
																	);
	// Lower button
	float theta_lower = 25.0 * M_PI / 180.0;
	GSphere* lower_button = new GSphere(Vertex3f(3.0*cos(theta_lower)+dx, 3.0*sin(theta_lower)+dy, 0.0+dz),
																	0.3,
																	*rock
																	);

	float theta_upper =  40.0 * M_PI / 180.0;
	GSphere* upper_button = new GSphere(Vertex3f(3.0*cos(theta_upper)+dx, 3.0*sin(theta_upper)+dy, 0.0+dz),
																			0.3,
																			*rock
																		  );

  objs.push_back(body);
  objs.push_back(head);
  objs.push_back(left_eye);
  objs.push_back(right_eye);
  objs.push_back(lower_button);
  objs.push_back(upper_button);
}

SnowMan::~SnowMan() { }

void SnowMan::applyTransform(const TMatrix & param) {
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    (*it)->applyTransform(param);
  }
}

// TODO: fix this implementation using code similar to
// the one in Scenery.cpp hitRay
float SnowMan::hitObject(Vertex3f & ray) {
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    (*it)->hitObject(ray);
  }
}

// TODO: fix this implementation using code similar to
// the one in Scenery.cpp hitRay
float SnowMan::hitObject(Vertex3f & ray, Vertex3f & normal) {
  std::list<Object*>::iterator it;
  for(it = objs.begin(); it != objs.end(); ++it) {
    (*it)->hitObject(ray, normal);
  }
}

float SnowMan::hitObject(Vertex3f & ray, Vertex3f & ret_n, Material * & ret_mat) {
  Material* first_mat;
  float best_t = hitObjectList(objs, ray, first_mat, ret_n);

  if(best_t < FLT_MAX) {
    ret_mat = first_mat;
  }

  return best_t;
}

Material* SnowMan::getMaterial() {
  return NULL;
}

void SnowMan::print() {
  this->snow->print();
  this->rock->print();
}
