#include "PointLightBuffer.h"
#include "glad/glad.h"
#include "graphics/Lighting.h"

template class SSBO<PointLightData>;

PointLightBuffer::PointLightBuffer() : SSBO<PointLightData>{}, lights{}{}

void PointLightBuffer::addPointLight(lighting::PointLight *pointLight) {
  this->lights.push_back(pointLight);
}

void PointLightBuffer::buffer() {
  std::vector<PointLightData> data = std::vector<PointLightData>{};

  // for(const auto &light : lights){
  //   data.push_back(PointLightData{
  //                    glm::vec4(light->getAmbient(), 1),
  //                    glm::vec4(light->getDiffuse(), 1),
  //                    glm::vec4(light->getSpecular(), 1),
  //                    glm::vec4(0, 3, 0, 1),
  //                    1.f, 0.09f ,0.032f
  //                  });
  // }

    data.push_back(PointLightData{
                     glm::vec4(glm::vec3{1.f, 0.f, 0.f}, 1),
                     glm::vec4(glm::vec3{1.f, 0.f, 0.f}, 1),
                     glm::vec4(glm::vec3{1.f, 0.f, 0.f}, 1),
                     glm::vec4(0, 3, 0, 1),
                     1.f, 0.09f ,0.032f
                   });

    unsigned int sbo = 0;

    
    PointLightData* d = new PointLightData[20];
    for(int i = 0; i < 20; i ++){
      d[i] =  PointLightData{
                     glm::vec4(glm::vec3{1.f, 0.f, 0.f}, 1),
                     glm::vec4(glm::vec3{1.f, 0.f, 0.f}, 1),
                     glm::vec4(glm::vec3{1.f, 0.f, 0.f}, 1),
                     glm::vec4(0, 3, 0, 1),
                     1.f, 0.09f ,0.032f
                   };
    }

    glEnable(GL_DEBUG_OUTPUT);
    glGenBuffers(1, &sbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, sbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(PointLightData) * 20, &d[0], GL_DYNAMIC_DRAW);

    // GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    // std::memcpy(p, data.data(), sizeof(PointLightData) * data.size());
    // glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, sbo);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);

    std::memcpy(p, data.data(), sizeof(PointLightData) * data.size());
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << std::hex << err << std::endl;
    }
  
  // this->updateBuffer(data);

  // delete data;
}
