#pragma once
#include <vector>
#include "Engine/math/math.h"
#include "Engine/RenderEngine/Shaders/shader.h"

class Renderer {
    public:
        void init() {
            shaderInit();
        }

        void shaderInit() {
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");
            shader.use();
        }

        unsigned int shaderID() { return shader.ID; }

        void setProjectionOrto();
        void setProjectionPers();
        void render();
    private:
        Shader shader;
        glm::mat4 orto = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
    
};