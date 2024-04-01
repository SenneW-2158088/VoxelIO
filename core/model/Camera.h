//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_CAMERA_H
#define VOXELIO_CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
    float last_x;
    float last_y;

    float yaw;      // horizontal angle
    float pitch;    // vertical angle
    const float FOV = 45.f;
    float sensitivity = 0.1f;

    const glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 direction;
    glm::vec3 position;
    glm::mat4 projection;
public:
    inline glm::vec3 getPosition() const {
        return position;
    }

    inline glm::mat4 getProjection() const {
        return projection;
    }

    glm::mat4 getView() const;

public:
    inline void setPosition(glm::vec3 position) {
        this->position = position;
    }

    void setDirectionByMouse(float x, float y);
    void setDirection(float yaw, float pitch);
public:
    Camera(glm::vec3 position, float yaw, float pitch, float sensitivity);
    ~Camera() = default;

};

class CameraBuilder {
private:
    float sensitivity = 100.f;
    glm::vec3 position{}, orientation{}, rotation{};

public:
    CameraBuilder() = default;
    inline CameraBuilder* setPosition(glm::vec3 position) { this->position = position; return this; }
    inline CameraBuilder* setOrientation(glm::vec3 orientation) { this->orientation = orientation; return this; }
    inline CameraBuilder* setRotation(glm::vec3 rotation) { this->rotation = rotation; return this; }
    inline CameraBuilder* setSensitivity(float sensitivity) { this->sensitivity = sensitivity; return this; };
    inline Camera* build() {
        return new Camera(position, 0.f, 0.f, sensitivity);
    }
};



#endif //VOXELIO_CAMERA_H
