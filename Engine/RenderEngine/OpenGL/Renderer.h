#pragma once
#include <vector>
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Shaders/shader.h"
#include "Engine/RenderEngine/Window/window.h"
#include "lib/stb/stb_image.h"

class Renderer {
    public:
        void init() {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_MULTISAMPLE);
        }

        void render();
    private:
};