//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_SHADER_H
#define VOXELIO_SHADER_H

#include <string>
#include <glm/glm.hpp>

unsigned int compileShader(const std::string &shaderSource, unsigned int shaderType);

class Shader {
private:
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int program;
public: // Getters
    [[nodiscard]] inline unsigned int getProgram() const { return program; };
    [[nodiscard]] inline unsigned int getVertex() const { return vertexShader; };
    [[nodiscard]] inline unsigned int getFragment() const { return fragmentShader; };
public: // Shader options
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
public: // Methods
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    const void use();
    void setBlockBinding(const std::string &uniformBlockName, int uniformBlockBinding) const;
    void setResourceBinding(const std::string &resourceBlockName, int resourceBlockBinding) const;
};


#endif //VOXELIO_SHADER_H
