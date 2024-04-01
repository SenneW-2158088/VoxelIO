//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_UNIFORM_H
#define VOXELIO_UNIFORM_H

#include <glm/glm.hpp>

namespace Uniform {

    class BaseUniform {
    protected:
        unsigned int UBO;
    };

    class GameUniform : public BaseUniform {
    private:
        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 viewPos;
    public:
    public:
        GameUniform(glm::mat4 projection, glm::mat4 view, glm::vec3 viewPos);
        ~GameUniform();

        inline glm::mat4 getProjection() const {
            return projection;
        }

        inline glm::mat4 getView() const {
            return view;
        }

        inline glm::vec3 getViewPos() const {
            return viewPos;
        }

    public:
        void setProjection(glm::mat4 projection);

        void setView(glm::mat4 view);

        void setViewPos(glm::vec3 viewPos);
    };
}


#endif //VOXELIO_UNIFORM_H
