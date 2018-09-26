#pragma once

#include "core/math/Vertex3f.h"

class Camera
{
  Vertex3f cam_pos; // Camera position
  Vertex3f look_at; // Point where camera is looking at
  Vertex3f avup;    // A View Up
  Vertex3f vup;     // View up (check if this is necessary)

  // New basis vectors
  Vertex3f j; // Unit vector i from coordinate system
  Vertex3f i; // Unit vector j from coordinate system
  Vertex3f k; // Unit vector k from coordinate system

  // Window position

public:
  Camera();
  Camera(Vertex3f cam_position, Vertex3f look_at, Vertex3f a_view_up, Vertex3f view_up);
  ~Camera();

  void setPosition(Vertex3f position);
  void setLookAt(Vertex3f position);
  void setAViewUp(Vertex3f position);

  Vertex3f getPosition();
  Vertex3f getLookAt();
  Vertex3f getAViewUp();

  void calcCoordSystemBasis();

  Vertex3f getI();
  Vertex3f getJ();
  Vertex3f getK();

//  void getCoord();
};
