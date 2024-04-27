#pragma once
#include "Components.h"


class PositionComponent : public Component {
    public:
        void init() override {
            pos = glm::vec4(1.0f);
        }

        void update(float dt) override {

        }

        glm::vec4& getPos() { return pos; }
        void setX_pos(float _x) { pos.x = _x; }
        void setY_pos(float _y) { pos.y = _y; }

    private:
        glm::vec4 pos;
};