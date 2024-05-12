//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Shader.h"
#include <exception>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>


//TODO: Refactor shader, load from file of from code
Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    program = glCreateProgram();
    vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);

    fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    glAttachShader(program, this->vertexShader);
    glAttachShader(program, this->fragmentShader);

    int success;
    char infoLog[512];
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw new std::exception;
    }
}

Shader::~Shader() {
    std::cout << "Deleting shader" << std::endl;
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteProgram(this->program);
}

const void Shader::use() {
    glUseProgram(program);
    GLuint error = glGetError();
    if(error != GL_NO_ERROR) {
        std::cout << "Failed to use shader program! "<< error << std::endl;
    }
}

// Compile shader from source file
unsigned int compileShader(const std::string &shaderSource, unsigned int shaderType) {
    unsigned int shader = glCreateShader(shaderType);

    std::ifstream stream;
    try {
        stream.open(shaderSource);
        std::stringstream shader_string;
        shader_string << stream.rdbuf();

        std::string shaderCode = shader_string.str();
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
            throw new std::exception;

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
    const int index = glGetUniformBlockIndex(this->program, uniformBlockName.c_str());
    if (index == GL_INVALID_INDEX) {
        std::cout << "Failed to find uniform block " << uniformBlockName << std::endl;
        return;
    }
    glUniformBlockBinding(this->program, index, uniformBlockBinding);
}

void Shader::setResourceBinding(const std::string &resourceBlockName, int resourceBlockBinding) const {
    const int index = glGetProgramResourceIndex(this->program, GL_SHADER_STORAGE_BLOCK, resourceBlockName.c_str());
    if(index == GL_INVALID_INDEX){
        std::cout << "Failed to find resource block " << resourceBlockName << std::endl;
        return;
    }
    glShaderStorageBlockBinding(this->program, index, resourceBlockBinding);
}

