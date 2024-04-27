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
            shaderInit();
        }

        void shaderInit() {
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");
        }

        void useShader() { shader.use(); }

        unsigned int shaderID() { return shader.ID; }

        void render();
        Shader shader;
};