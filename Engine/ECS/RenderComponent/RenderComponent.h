#pragma once
#include "Engine/ECS/Components.h"

class RenderComponent : public Component {
    public:
        void init() override {
            model = glm::mat4(1.0f);
            view = glm::mat4(1.0f);
            projection = glm::mat4(1.0f);
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/RenderComponent/renderVertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/RenderComponent/renderFragment.fs");
        }

        void initShaders() {

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

        void setModel(std::string modelPath) {
            mdl.load(modelPath);
        }

        glm::mat4& getModelMat() { return model; }

        void getCam(Icamer2D& cam) {
            projection = cam.projection();
            view = cam.view();
        }

    private:
        glm::mat4 model;
        glm::mat4 projection;
        glm::mat4 view;
        Shader shader;
        Model mdl;
};