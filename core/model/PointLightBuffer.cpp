#include "PointLightBuffer.h"
#include "glad/glad.h"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Lighting.h"

template class SSBO<PointLightData>;

PointLightBuffer::PointLightBuffer() : SSBO<PointLightData>{}, lights{}{}

void PointLightBuffer::addPointLight(lighting::PointLight *pointLight) {
  this->lights.push_back(pointLight);
}

void PointLightBuffer::buffer() {
  std::vector<PointLightData> data = std::vector<PointLightData>{};

  for(const auto &light: lights){
    data.push_back(PointLightData{
                     glm::vec4(light->getAmbient(), 1.f),
                     glm::vec4(light->getDiffuse(), 1.f),
                     glm::vec4(light->getSpecular(), 1.f),
                     glm::vec4(light->getPosition(), 0.f),
                     glm::vec4(light->getDistance(), 1.f),
                   });
    std::cout << "++ adding pointlight" << std::endl;
  }

  unsigned int sbo;
  glGenBuffers(1, &sbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, sbo);
  const auto size = sizeof(PointLightData) * data.size();
  std::cout << "data size " << sizeof(PointLightData) << " * " << data.size() << std::endl;
  glBufferData(GL_SHADER_STORAGE_BUFFER, size, data.data(), GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, sbo);
  void* ptr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
  PointLightData* lights = reinterpret_cast<PointLightData*>(ptr);
  for (int i = 0; i < data.size(); i++) {
      std::cout << "Light " << i << " " << glm::to_string(lights[i].ambient) << std::endl;
      std::cout << glm::to_string(lights[i].distance) << std::endl;
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
  // glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  // this->updateBuffer(data);
}
