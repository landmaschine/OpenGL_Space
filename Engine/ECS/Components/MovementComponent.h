#pragma once
#include "../ECS.h"
#include "Engine/Pyhsics/physics.h"
#include <glm/glm.hpp>
#include "Engine/RenderEngine/Window/window.h"



class MovementComponent : public Component {
    public:
        void init() override {
            pos = glm::vec3(1.0f);
            velocity = glm::vec3(0.0f);
            trans = glm::mat4(1.0f);
            rotMat = glm::mat4(1.0f);
            mass = 10;
            speed = 100;
            speedMod = 1;
            dt = 0;
            scale = 200.0f;
            trans = glm::scale(trans, glm::vec3(scale));
        }

        void update() override {
            mov.calcTransform(trans, rotMat, window, dt, mass, speedMod, velocity, pos);
        }

        glm::mat4& transform() { return trans; }
        glm::mat4& rotTransform() { return rotMat; }
        glm::vec3& Pos() { return pos; }
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