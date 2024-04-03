//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_TRIANGLE_H
#define VOXELIO_TRIANGLE_H

#include <vector>
#include <model/Entity.h>
#include <graphics/Mesh.h>
#include <graphics/Shader.h>

class Triangle : public Entity {
private:
    unsigned int VAO, VBO, EBO;

    Shader* shader;

    const std::vector<Mesh::Vertex> vertices = {
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}}
    };
    const std::vector<unsigned int> indices = {0, 1, 2};
public:
    Triangle();
    void update(float dt) override;
    void draw() override;
};


#endif //VOXELIO_TRIANGLE_H
