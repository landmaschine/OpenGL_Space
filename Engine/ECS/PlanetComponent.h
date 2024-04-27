#pragma once
#include "Components.h"

class PlanetComponent : public Component {
    public:
        void init() override {
            tmpdt = 0;
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(5.f, 5.0f, -1000.f));
            model = glm::scale(model, glm::vec3(2.f));
        }

        void update(float dt) override {
                rot.planetRotation(model, dt);
        }

        void setdt(float dt) {
            this->dt = dt;
        }

        glm::mat4& rotMat() {
            return model;
        }

    private:
        Physics::Movement rot;
        glm::mat4 model;
        float dt;
        float tmpdt;
};