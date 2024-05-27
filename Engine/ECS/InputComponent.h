#pragma once
#include "ECS.h"

class InputComponent : public Component {
    public:
        glm::vec2 direction = glm::vec2(0.f);
        float speedMod = 0;
};