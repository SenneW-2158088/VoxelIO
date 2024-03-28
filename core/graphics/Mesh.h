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

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            std::vector<unsigned int> textures;

        public:
            BaseMesh();
            BaseMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> textures);

            // Simple Mesh operations
            virtual void move(glm::vec3 position);
            virtual void rotate();
            virtual void scale();

            virtual void draw(Shader &shader) = 0;
    };

//    Standard Mesh class for basic objects
    class Mesh : BaseMesh{
    private:
        glm::vec3 size;
        glm::vec3 position;
    };

//    Instanced Mesh class for instanced objects
    class InstancedMesh : BaseMesh {
    private:
        std::vector<glm::vec3> positions;
        std::vector<glm::vec4> models;
    };
}


#endif //VOXELIO_MESH_H
