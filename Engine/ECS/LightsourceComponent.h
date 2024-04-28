#pragma once
#include "Components.h"

class LightsourceComponent : public Component {
    public:
        void init() override {
            objColor = glm::vec3(1.f, 0.5f, 0.31f);
            lightColor = glm::vec3(1.f, 1.f, 1.f);
            lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

            trans = glm::mat4(1.0f);

            proj = glm::mat4(1.0f);
            view = glm::mat4(1.0f);

            lightCubeShader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/light.vs",
                                       "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/light.fs");

            lightShader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                                       "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");
        }

        void update(float dt) override {
            
        }

        void draw() override {
            lightShader.use();
            lightShader.setVec3("objectColor", objColor);
            lightShader.setVec3("lightColor", lightColor);
            lightShader.setMat4("projection", proj);
            lightShader.setMat4("view", view);
            lightShader.setVec3("lightPos", lightPos);
            trans = glm::mat4(1.0f);
            trans = glm::translate(trans, glm::vec3(1.f, 2.f, -10.f));
            lightShader.setMat4("model", trans);
            light.Draw(lightShader.ID);

            /*
            lightCubeShader.use();
            lightCubeShader.setMat4("projection", proj);
            lightCubeShader.setMat4("view", view);
            trans = glm::mat4(1.0f);
            trans = glm::translate(trans, glm::vec3(10.f, -1.f, -10.f));
            trans = glm::scale(trans, glm::vec3(0.5f));
            lightCubeShader.setMat4("model", trans);
            lightCube.Draw(lightCubeShader.ID);
            */
        }

        void loadModel(std::string path) {
            light.load(path);
            lightCube.load(path);
        }

        void setCam(Icamer2D& cam) {
            proj = cam.projection();
            view = cam.view();
        }

    private:
        Shader lightShader;
        Shader lightCubeShader;
        glm::vec3 objColor;
        glm::vec3 lightColor;
        glm::vec3 lightPos;
        
        Model light;
        Model lightCube;
        glm::mat4 trans;
        glm::mat4 proj;
        glm::mat4 view;

};