#include "PointLightBuffer.h"
#include "graphics/Lighting.h"

template class SSBO<PointLightData>;

PointLightBuffer::PointLightBuffer() : SSBO<PointLightData>{}, lights{}{}

void PointLightBuffer::addPointLight(lighting::PointLight *pointLight) {
  this->lights.push_back(pointLight);
}

void PointLightBuffer::buffer() {
  std::vector<PointLightData> *data = new std::vector<PointLightData>{};

  for(const auto &light : lights){
    data->push_back(PointLightData{
                   0,0,0,
                     glm::vec4(light->getAmbient(), 1),
                     glm::vec4(light->getDiffuse(), 1),
                     glm::vec4(light->getSpecular(), 1),
                     glm::vec4(0, 1, 2, 1),
                   });
  }
  
  this->updateBuffer(&(*data)[0], lights.size());
}
