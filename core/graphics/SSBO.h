#pragma once

#include "glad/glad.h"

/* Here lies the most beautiful piece of software, the magical infinite buffer */
template<class T>
class SSBO {
private:
  unsigned int id; // used for binding to the correct index
  unsigned int SBO;
public:
  void setId(unsigned int id) { this->id = id; };
public:
  unsigned int getId() const { return id; };
  unsigned int getSBO() const {return SBO; };
public:
  // Update the buffer with the supplied array
  void updateBuffer(T data[], unsigned int size) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * size, data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  }
public:
  SSBO() : id{0} {
    // Create SBBO buffer
    glGenBuffers(1, &SBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, id, SBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  };

  ~SSBO<T>() {
    glDeleteBuffers(1, &SBO);
  };

  void bind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, getId(), SBO);
  };
};
