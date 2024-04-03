//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/quaternion_geometric.hpp"

#include <glm/gtc/matrix_transform.hpp>

void Camera::setDirection(float yaw, float pitch) {
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction = glm::normalize(direction);
}

PerspectiveCamera::PerspectiveCamera() : Camera() {}

glm::mat4 PerspectiveCamera::getProjection() const {
  return glm::perspective(field, aspect, NEAR, FAR);
}

glm::mat4 PerspectiveCamera::getView() const {
  return glm::lookAt(position, position + direction, up);
}
