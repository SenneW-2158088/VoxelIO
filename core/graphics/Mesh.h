//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_MESH_H
#define VOXELIO_MESH_H

#include "graphics/Material.h"
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

            glm::vec3 translation; // used to make mesh coordinates fit to world coordinates
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            Material* material;

        public:
            BaseMesh();
            BaseMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material);

            // Simple Mesh operations
            virtual void move(const glm::vec3 position);
            virtual void rotate(const float rotation, const glm::vec3 axis);
            virtual void scale(const glm::vec3 scale);
            virtual void scaleToWorld(const glm::vec3 scale);


            virtual void draw(Shader *shader);
        public:
            inline std::vector<Vertex> getVertices() const {return vertices;};
            inline glm::vec3 getTranslation() const {return translation; };
    };

//    Standard Mesh class for basic objects
    class Mesh : public BaseMesh{
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material);
    };

//    Instanced Mesh class for instanced objects
    class InstancedMesh : public BaseMesh {
    private:
        unsigned int VBO_INSTANCED{};
        std::vector<glm::mat4> models;
    public:
        InstancedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material *material, std::vector<glm::vec3> positions, glm::vec3 position);
        void draw(Shader *shader) override;
        void move(const glm::vec3 position) override;
    };
}


#endif //VOXELIO_MESH_H
