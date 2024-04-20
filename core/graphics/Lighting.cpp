#include "Lighting.h"

using namespace lighting;

Light::Light()
    : active{true}, ambient{1.f, 1.f, 1.f}, diffuse{.8f, .2f, .8f}, specular{1.f, 1.f, 1.f} {}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : active{true}, ambient{ambient}, diffuse{diffuse}, specular{specular} {}


DirectionalLight::DirectionalLight()
    : Light{}, direction{-2.f, -2.f, -2.f} {}

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
    : Light{ambient, diffuse, specular}, direction{direction} {}
