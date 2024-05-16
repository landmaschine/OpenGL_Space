#pragma once
#include "Engine/ECS/depComponents.h"

class LightsourceComponent : public Component {
    public:
        void init() override {
            objColor = glm::vec3(1.f, 0.5f, 0.31f);
            lightColor = glm::vec3(1.f, 1.f, 1.f);
            lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
            playerPos = glm::vec3(1.0f);

            trans = glm::mat4(1.0f);

            proj = glm::mat4(1.0f);
            view = glm::mat4(1.0f);

            lightShader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/lightSource/shaders/light.vs",
                                   "/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/lightSource/shaders/light.fs");

            lightCubeShader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/lightSource/shaders/lightCube.vs",
                                       "/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/lightSource/shaders/lightCube.fs");
            
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
            lightShader.setVec3("viewPos", playerPos);
            trans = glm::mat4(1.0f);
            trans = glm::translate(trans, glm::vec3(1.f, 2.f, -11.f));
            lightShader.setMat4("model", trans);

            
            lightCubeShader.use();
            lightCubeShader.setMat4("projection", proj);
            lightCubeShader.setMat4("view", view);
            trans = glm::mat4(1.0f);
            trans = glm::translate(trans, playerPos);
            lightCubeShader.setMat4("model", trans);
            
        }


        void setCam(Icamer2D& cam) {
            proj = cam.projection();
            view = cam.view();
        }

        void getPlayerPos(glm::vec3 playerPos) {
            this->playerPos = playerPos;
        }

    private:
        Shader lightShader;
        Shader lightCubeShader;
        glm::vec3 objColor;
        glm::vec3 lightColor;
        glm::vec3 lightPos;
        glm::vec3 playerPos;
        
        glm::mat4 trans;
        glm::mat4 proj;
        glm::mat4 view;

};