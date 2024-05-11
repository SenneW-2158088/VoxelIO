#include "Lighting.h"
#include <queue>

using namespace lighting;

Light::Light()
    : active{true}, ambient{1.f, 1.f, 1.f}, diffuse{.8f, .2f, .8f}, specular{1.f, 1.f, 1.f} {}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : active{true}, ambient{ambient}, diffuse{diffuse}, specular{specular} {}


DirectionalLight::DirectionalLight()
    : Light{}, direction{-2.f, -2.f, -2.f} {}

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
    : Light{ambient, diffuse, specular}, direction{direction} {}


PointLight::PointLight():
    Light{}, position{0.f, 9.f, 0.f}, constant{1.f}, linear{.09f}, quadratic{.032f}
{}
PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic) : 
    Light{ambient, diffuse, specular}, position{position}, constant{constant}, linear{linear}, quadratic{quadratic}
{}
