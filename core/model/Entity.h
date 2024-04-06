//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_ENTITY_H
#define VOXELIO_ENTITY_H

#include <glm/glm.hpp>
#include <string>

class Entity {
protected:
    glm::vec3 position{};

public:
    inline glm::vec3 getPosition() { return position; }
    virtual std::string getName() { return "[Entity ()]";};

public:
    inline void setPosition(glm::vec3 position) { this->position = position; }

public:
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};


#endif //VOXELIO_ENTITY_H
