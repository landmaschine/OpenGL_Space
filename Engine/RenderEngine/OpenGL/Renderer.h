#pragma once
#include <vector>
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Shaders/shader.h"
#include "Engine/RenderEngine/Window/window.h"
#include "lib/stb/stb_image.h"

class Renderer {
    public:
        void init() {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            shaderInit();
        }

        void shaderInit() {
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");
        }

        void useShader() { shader.use(); }

        unsigned int shaderID() { return shader.ID; }

        void setProjectionOrto(Window& window);
        void setProjectionPers(Window& window);
        void render();
        Shader shader;
    private:
        glm::mat4 orto = glm::mat4(1.0f);
};