#pragma once

#include "manager/InputManager.h"
#include "model/Camera.h"

class CameraHandler : public InputListener {
private:
  float sensitivity;
  bool firstLoad;
  double x, y;
  double offset_x, offset_y;
public:
  CameraHandler(float sensitivity);
  void onMouseMove(double x, double y) override;
  void updateCamera(Camera* camera);
};
