#pragma once
#include "../ECS.h"
#include "Engine/Pyhsics/physics.h"
#include <glm/glm.hpp>
#include "Engine/RenderEngine/Window/window.h"


class PositionComponent : public Component {
    public:
        void init() override {
            pos = glm::vec4(1.0f);
        }

        void update() override {

        }

        glm::vec4& getPos() { return pos; }
        void setX_pos(float _x) { pos.x = _x; }
        void setY_pos(float _y) { pos.y = _y; }

    private:
        glm::vec4 pos;
};