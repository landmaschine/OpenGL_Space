#pragma once
#include "depComponents.h"

class PlanetComponent : public Component {
    public:
        void init() override {
            rotMat = glm::mat4(1.0f);
            if(!entity->hasComponent<PositionComponent>()) {
                std::cout << "Entity has no Position Component!" << std::endl;
            }
            pos = &entity->getComponent<PositionComponent>();
        }

        void update() override {
            pos->transform = rotMat;
        }

        void setinitPos(float x, float y, float z, float scale) {
            rotMat = glm::translate(rotMat, glm::vec3(x, y, z));
            rotMat = glm::scale(rotMat, glm::vec3(scale));
        }

        glm::mat4 rotMat;
    private:
        PositionComponent* pos;
};