#include "CameraHandler.h"
#include <iostream>

CameraHandler::CameraHandler(float sensitivity): sensitivity{sensitivity}{}

void CameraHandler::onMouseMove(double x, double y) {
  offset_x = x - this->x;
  offset_y = this->y - y;
  this->y = y;
  this->x = x;
  // std::cout << offset_x << " " << offset_y << std::endl;
}

void CameraHandler::updateCamera(Camera *camera) const {
  float yaw = camera->getYaw();
  float pitch = camera->getPitch();

  if (pitch >= 89.f){
    pitch = 89.f;
  }

  if (pitch <= -89.f){
    pitch = -89.f;
  }

  std::cout << yaw + this->offset_x << " " << pitch + this->offset_y << std::endl;

  camera->setDirection(yaw + this->offset_x * sensitivity, pitch + this->offset_y * sensitivity);
}
