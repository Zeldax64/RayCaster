#include "app/objects/SnowMan.h"

SnowMan::SnowMan() {

  // Body
  GSphere* body = new GSphere(Vertex3f(0.0, 0.0, 0.0),
                                3.0,
                                1.0, 1.0, 1.0);

  // Head
  GSphere* head = new GSphere(Vertex3f(0.0, 4.0, 0.0),
                                1.0,
                                1.0, 1.0, 1.0
                      );

  // Left eye
  GSphere* left_eye = new GSphere(Vertex3f(1.0, 4.25, 0.45),
                                  0.15,
                                  0.0, 0.0, 0.0
                                );

  // Right eye
  GSphere* right_eye = new GSphere(Vertex3f(1.0, 4.25, -0.45),
                                  0.15,
                                  0.0, 0.0, 0.0
                                  );
  // Lower button
  float theta_lower = 25.0 * M_PI / 180.0;
  GSphere* lower_button = new GSphere(Vertex3f(3.0*cos(theta_lower), 3.0*sin(theta_lower), 0.0),
                                  0.3,
                                  0.0, 0.0, 0.0
                                  );

  float theta_upper =  40.0 * M_PI / 180.0;
  GSphere* upper_button = new GSphere(Vertex3f(3.0*cos(theta_upper), 3.0*sin(theta_upper), 0.0),
                                      0.3,
                                      0.0, 0.0, 0.0
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
    std::cout << "Passou aqui \n";
  }
}

float SnowMan::hitObject(Vertex3f & ray, Vertex3f & ret_n, Material * & ret_mat) {

}

Material* SnowMan::getMaterial() {
  return NULL;
}

void SnowMan::print() {}
