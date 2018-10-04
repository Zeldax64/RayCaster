#include "core/camera/Camera.h"

Camera::Camera() { this->setFOV(90.0); }
Camera::Camera(Vertex3f cam_position, Vertex3f look_at, Vertex3f a_view_up, Vertex3f view_up , float fov) {
  this->setPosition(cam_position);
  this->setLookAt(look_at);
  this->setAViewUp(a_view_up);
  this->calcCoordSystemBasis();
  this->setFOV(fov);
}
Camera::~Camera() {}

void Camera::setPosition(Vertex3f position) { cam_pos = position; }
void Camera::setLookAt(Vertex3f position) { look_at = position; }
void Camera::setAViewUp(Vertex3f position) { avup = position; }
void Camera::setFOV(float fov) { this->fov = fov; }

Vertex3f Camera::getPosition() { return cam_pos; }
Vertex3f Camera::getLookAt() { return look_at; }
Vertex3f Camera::getAViewUp() { return avup; }
float Camera::getFOV() { return fov; }

void Camera::calcCoordSystemBasis() {
  Vertex3f look_at_p0 = cam_pos - look_at;
  this->k = look_at_p0.unit();

  this->vup = avup - cam_pos;
  this->i = (vup.crossProduct(k)).unit();
  this->j = k.crossProduct(i);
}

Vertex3f Camera::getI() { return i; }
Vertex3f Camera::getJ() { return j; }
Vertex3f Camera::getK() { return k; }

void Camera::print() {
  std::cout << "Cam_pos \n";

}
