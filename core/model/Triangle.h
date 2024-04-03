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
    Mesh::Mesh* mesh;
    Shader* shader;

public:
    Triangle();
    void update(float dt) override;
    void draw() override;
};


#endif //VOXELIO_TRIANGLE_H
