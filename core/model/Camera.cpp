//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(){}
Camera::Camera(glm::vec3 position, glm::vec3 direction) : position{position}, direction{direction} {
  yaw = atan2(direction.z, direction.x) * 180.f / M_PI;
  pitch = atan2(direction.y, sqrt(direction.x * direction.x + direction.z * direction.z)) * 180.0f / M_PI;
}

void Camera::setDirection(float yaw, float pitch) {
  this->yaw = yaw;
  this->pitch = pitch;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction = glm::normalize(direction);
}

PerspectiveCamera::PerspectiveCamera(){}
PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 direction, float fov, float aspect) : Camera(position, direction){
  this->field = fov;
  this->aspect = aspect;
}

glm::mat4 PerspectiveCamera::getProjection() const {
  return glm::perspective(glm::radians(field), aspect, NEAR, FAR);
}

glm::mat4 PerspectiveCamera::getView() const {
  return glm::lookAt(position, position + direction, up);
}
