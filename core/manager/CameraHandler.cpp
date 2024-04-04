#include "CameraHandler.h"
#include <iostream>

CameraHandler::CameraHandler(float sensitivity): sensitivity{sensitivity}, firstLoad(true), y{}, x{}{}

void CameraHandler::onMouseMove(double x, double y) {
  if(firstLoad && x != 0 && y != 0){
    std::cout << "first " << x << " " << y << std::endl;
    this->y = y;
    this->x = x;
    firstLoad = false;
  }

  offset_x = x - this->x;
  offset_y = this->y - y;

  this->y = y;
  this->x = x;
}

void CameraHandler::updateCamera(Camera *camera) {
  if (firstLoad) {
    
    float yaw = camera->getYaw();
    float pitch = camera->getPitch();
    camera->setDirection(yaw, pitch);
    return;
  }

  float yaw = camera->getYaw() + this->offset_x * sensitivity;
  float pitch = camera->getPitch() + this->offset_y * sensitivity;

  if (pitch >= 89.f){
    pitch = 89.f;
  }

  if (pitch <= -89.f){
    pitch = -89.f;
  }

  // std::cout << yaw << " " << pitch << std::endl;

  camera->setDirection(yaw, pitch);
}
