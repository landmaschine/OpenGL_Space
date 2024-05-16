#pragma once
#include <vector>
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Shaders/shader.h"
#include "Engine/RenderEngine/Window/window.h"
#include "lib/stb/stb_image.h"
#include "Engine/ECS/depComponents.h"

class Renderer {
    public:
        void init() {
            glEnable(GL_MULTISAMPLE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        void render();
};