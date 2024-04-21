#pragma once

#include "graphics/Lighting.h"
#include "graphics/SSBO.h"
#include <vector>


struct PointLightData {
    float constant;
    float linear;
    float quadratic;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 position;
};


class PointLightBuffer : public SSBO<PointLightData> {
private:
  std::vector<lighting::PointLight*> lights;
public:
  PointLightBuffer();
  void addPointLight(lighting::PointLight* pointlight);
  void buffer();
};
