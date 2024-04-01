//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::setDirectionByMouse(float x, float y) {
    float offset_x = x - this->last_x;
    float offset_y = this->last_y - y;

    last_x = x;
    last_y = y;

    yaw += offset_x * this->sensitivity;
    pitch += offset_y * this->sensitivity;

    setDirection(yaw, pitch);
}

void Camera::setDirection(float yaw, float pitch) {
    if (pitch >= 89.0f){
        pitch = 89.0f;
    }
    if (pitch <= -89.0f){
        pitch = -89.0f;
    }

    this->yaw = yaw;
    this->pitch = pitch;

    glm::vec3 new_direction{
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch)),
    };

    this->direction = glm::normalize(new_direction);
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(
        this->position,
        this->position + this->direction,
        this->up
    );
}

Camera::Camera(glm::vec3 position, float yaw, float pitch, float sensitivity) {
    this->setPosition(position);
    this->setDirection(yaw, pitch);
}
