#pragma once
#include <vector>
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Shaders/shader.h"
#include "Engine/RenderEngine/Window/window.h"

class Renderer {
    public:
        void init() {
            shaderInit();
        }

        void shaderInit() {
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");
            shader.use();
            shader.setInt("texture1", 1);
        }

        void useShader() { shader.use(); }

        unsigned int shaderID() { return shader.ID; }

        void setProjectionOrto();
        void setProjectionPers();
        void render();
        Shader shader;
    private:
        glm::mat4 orto = glm::mat4(1.0f);
};