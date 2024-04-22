#pragma once
#include "ECS.h"
#include "Engine/RenderEngine/Shaders/shader.h"
#include "Engine/Pyhsics/physics.h"
#include <glm/glm.hpp>
#include "Engine/RenderEngine/Window/window.h"

class PositionComponent : public Component {
    public:
        void init() override {
            pos = glm::vec4(1.0f);
        }

        void update() override {

        }

        glm::vec4& getPos() { return pos; }
        void setX_pos(float _x) { pos.x = _x; }
        void setY_pos(float _y) { pos.y = _y; }

    private:
        glm::vec4 pos;
};

class RenderComponent : public Component {
    public:
        void init() override {
            trans = glm::mat4(1.0f);
            rotMat = glm::mat4(1.0f);

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0); 
            glBindVertexArray(0);

            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/vertex.vs",
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/Shaders/shaderfiles/fragment.fs");
            shader.use();
        }

        void setPos(glm::vec4 _pos) {
            pos = _pos;
        }

        glm::mat4& transform() { return trans; }
        glm::mat4& rotTransforms() { return rotMat; }

        void update() override {
            
        }

        void draw() override {
            unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
            unsigned int rottransformLoc = glGetUniformLocation(shader.ID, "rotTransform");
            glUniformMatrix4fv(rottransformLoc, 1, GL_FALSE, glm::value_ptr(rotMat));
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

    private:
        unsigned int VBO;
        unsigned int VAO;
        glm::vec4 pos;
        glm::mat4 trans;
        glm::mat4 rotMat;
        Shader shader;

        float vertices[18] = {
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
        };
};

class MovementComponent : public Component {
    public:
        void init() override {
            pos = glm::vec3(1.0f);
            velocity = glm::vec3(1.0f);
            trans = glm::mat4(1.0f);
            rotMat = glm::mat4(1.0f);
            mass = 10;
            speed = 100;
            speedMod = 1;
            dt = 0;
            scale = 0.4f;
            trans = glm::scale(trans, glm::vec3(scale));
        }

        void update() override {
            mov.calcTransform(trans, rotMat, window, dt, mass, speedMod, velocity, pos);
        }

        glm::mat4& transform() { return trans; }
        glm::mat4& rotTransform() { return rotMat; }
        glm::vec3& getPos() { return pos; }
        glm::vec3& getVel() { return velocity; }
        float& getMass() { return mass; }
        int& getSpeed() { return speed; }
        int& getSpeedMod() { return speedMod; }
        void setX_pos(float _x) { pos.x = _x; }
        void setY_pos(float _y) { pos.y = _y; }
        void setX_vel(float _x) { velocity.x = _x; }
        void setY_vel(float _y) { velocity.y = _y; }
        void frameTime(float _dt) { dt = _dt; }

        void getWindow(Window& _win) { window = _win; }

    private:
        Movement mov;
        glm::vec3 pos;
        glm::vec3 velocity;
        glm::mat4 trans;
        glm::mat4 rotMat;
        Window window;
        float mass;
        float dt;
        float scale;
        int speed;
        int speedMod;
};