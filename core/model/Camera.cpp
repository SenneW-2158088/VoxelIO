//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(){}
Camera::Camera(glm::vec3 position, glm::vec3 direction) : position{position}, direction{direction} {}

void Camera::setDirection(float yaw, float pitch) {
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
