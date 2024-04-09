//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_MESH_H
#define VOXELIO_MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <graphics/Shader.h>

namespace Mesh {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    class BaseMesh {
        protected:
            unsigned int VAO{};
            unsigned int VBO{};
            unsigned int IBO{};

            glm::mat4 model;

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            std::vector<unsigned int> textures;

        public:
            BaseMesh();
            BaseMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> textures);

            // Simple Mesh operations
            virtual void move(const glm::vec3 position);
            virtual void rotate(const float rotation, const glm::vec3 axis);
            virtual void scale(const glm::vec3 scale);

            virtual void draw(Shader *shader);
        public:
            inline std::vector<Vertex> getVertices() const {return vertices;};
    };

//    Standard Mesh class for basic objects
    class Mesh : public BaseMesh{
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> textures);
    };

//    Instanced Mesh class for instanced objects
    class InstancedMesh : public BaseMesh {
    private:
        unsigned int VBO_INSTANCED{};
        std::vector<glm::mat4> models;
    public:
        InstancedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> textures, std::vector<glm::vec3> positions);
        void draw(Shader *shader) override;
    };
}


#endif //VOXELIO_MESH_H
