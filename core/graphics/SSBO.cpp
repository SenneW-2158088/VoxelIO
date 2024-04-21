#include "SSBO.h"

// template<class T>
// SSBO<T>::SSBO() : id{0} {
//   // Create SBBO buffer
//   glGenBuffers(1, &SBO);
//   glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
//   glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
//   glBindBufferBase(GL_SHADER_STORAGE_BUFFER, id, SBO);
//   glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
// }

// template<class T>
// SSBO<T>::~SSBO<T>() {
//   glDeleteBuffers(1, SBO);
// }

// template<class T>
// void SSBO<T>::bind() const {
//   glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
//   glBindBufferBase(GL_SHADER_STORAGE_BUFFER, getId(), SBO);
// }

// template<class T>
// void SSBO<T>::updateBuffer(T data[], unsigned int size){
//   glBindBuffer(GL_SHADER_STORAGE_BUFFER, SBO);
//   glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * size, data, GL_DYNAMIC_DRAW);
//   glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
// }



