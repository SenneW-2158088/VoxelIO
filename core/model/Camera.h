//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_CAMERA_H
#define VOXELIO_CAMERA_H

#include <glm/glm.hpp>

/*
  Basic Camera interface that represents a perspective camera
*/
class Camera {
protected:
  const glm::vec3 up = glm::vec3(0.f, 1.f, 0.f); // We use the y-axis for up

  float yaw, pitch;
  glm::vec3 position;
  glm::vec3 direction;

public:
  virtual glm::vec3 getPosition() const = 0;
  virtual glm::mat4 getProjection() const = 0;
  virtual glm::mat4 getView() const = 0;
  inline float getYaw() const { return yaw; }
  inline float getPitch() const { return pitch; }
  inline glm::vec3 getDirection() const { return direction; };

public:
  inline void setPosition(glm::vec3 position) { this->position = position; };
  inline void setDirection(glm::vec3 direction) {
    this->direction = direction;
  };
  void setDirection(float yaw, float pitch);

public:
  Camera();
  explicit Camera(glm::vec3 position, glm::vec3 direction);
};

class PerspectiveCamera : public Camera {
private:
  const float NEAR = .5f;
  const float FAR = 100.f;
  float field;  // Field Of View
  float aspect; // Aspect ratio
public:
  PerspectiveCamera();
  explicit PerspectiveCamera(glm::vec3 position, glm::vec3 direction, float fov,
                             float aspect);

public:
  inline void setField(float field) { this->field = field; };
  inline void setAspect(float aspect) { this->aspect = aspect; };

public:
  inline glm::vec3 getPosition() const override { return this->position; };
  glm::mat4 getProjection() const override;
  glm::mat4 getView() const override;
};

class PerspectiveCameraBuilder {
private:
  glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
  glm::vec3 direction = glm::vec3(0.f, 0.f, 1.f);
  float field = 45.f;        // Field Of View
  float aspect = 16.f / 9.f; // Aspect ratio

public:
  PerspectiveCameraBuilder() = default;
  inline PerspectiveCameraBuilder *setPosition(glm::vec3 position) {
    this->position = position;
    return this;
  }
  inline PerspectiveCameraBuilder *setDirection(glm::vec3 direction) {
    this->direction = direction;
    return this;
  }
  inline PerspectiveCameraBuilder *setField(float field) {
    this->field = field;
    return this;
  }
  inline PerspectiveCameraBuilder *setAspect(float aspect) {
    this->aspect = aspect;
    return this;
  };
  inline PerspectiveCamera *build() {
    return new PerspectiveCamera(position, direction, field, aspect);
  };
};

#endif // VOXELIO_CAMERA_H
