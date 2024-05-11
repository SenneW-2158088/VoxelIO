#pragma once

#include "glad/glad.h"
#include <cstring>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

/* Here lies the most beautiful piece of software, the magical infinite buffer */
template<class T>
class SSBO {
private:
  unsigned int id; // used for binding to the correct index
  unsigned int SBO;
public:
  void setId(unsigned int id) { this->id = id; };
public:
  unsigned int getId() const { return this->id; };
  unsigned int getSBO() const {return SBO; };
public:
    SSBO() {
        // glGenBuffers(1, &SBO);
        // glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
        // // glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW); // Allocate with null initially
        // glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    ~SSBO() {
        glDeleteBuffers(1, &SBO);
    }

    void updateBuffer(std::vector<T> data) {
        std::cout << "Updating buffer with size: " << sizeof(T) << " * " << data.size() << std::endl;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * data.size(), data.data(), GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, SBO);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    }

    void bind(int bindingPoint) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, SBO);
    }
};
