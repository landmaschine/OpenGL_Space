#pragma once
#include "Components.h"

class RenderComponent : public Component {
    public:
        void init() override {
            model = glm::mat4(1.0f);
            view = glm::mat4(1.0f);
            projection = glm::mat4(1.0f);
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");
        }

        void update(float dt) override {

        }

        void draw() override {
            shader.use();
            shader.setMat4("projection", projection);
            shader.setMat4("view", view);
            shader.setMat4("model", model);
            mdl.Draw(shader.ID);
        }

        ~RenderComponent() override {
    
        }

        void setTex(std::string path) {
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
        }

        void setModel(std::string modelPath) {
            mdl.load(modelPath);
        }

        glm::mat4& getModelMat() { return model; }

        void getCam(Icamer2D& cam) {
            projection = cam.projection();
            view = cam.view();
        }

    private:
        int width, height, nrChannels;
        glm::mat4 model;
        glm::mat4 projection;
        glm::mat4 view;
        Shader shader;
        Model mdl;
};