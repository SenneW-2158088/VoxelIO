//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    this->program = glCreateProgram();
    this->vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    glAttachShader(this->program, this->vertexShader);

    this->fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    glAttachShader(this->program, this->fragmentShader);

    glLinkProgram(this->program);

}

Shader::~Shader() {
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteProgram(this->program);
}

const void Shader::use() {
    glUseProgram(this->program);
}

// Compile shader from source file
unsigned int compileShader(const std::string &shaderSource, unsigned int shaderType) {
    unsigned int shader = glCreateShader(shaderType);

    try {
       // loading shader source from file
        std::ifstream file(shaderSource);
        std::stringstream stream;
        stream << file.rdbuf();

        std::string shaderCode = stream.str();
        const char* src = shaderCode.c_str();

        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

        // Check for errors
        if (result == GL_FALSE) {
            // Obtain error length
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            // Get error message
            char *message = (char *) alloca(length * sizeof(char));
            glGetShaderInfoLog(shader, length, &length, message);

            std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << message << std::endl;

            // Delete shader program from memory
            glDeleteShader(shader);

            return 0;
        }

    } catch (std::ifstream::failure &e) {
        glDeleteShader(shader);
        std::cout << e.what() << std::endl;
    }

    return shader;
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->program, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->program, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->program, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(this->program, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(this->program, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(this->program, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(this->program, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(this->program, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(this->program, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setBlockBinding(const std::string &uniformBlockName, int uniformBlockBinding) const {
    glUniformBlockBinding(this->program, glGetUniformBlockIndex(this->program, uniformBlockName.c_str()), uniformBlockBinding);
}
