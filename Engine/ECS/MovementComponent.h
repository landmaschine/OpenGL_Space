#pragma once
#include "Components.h"

class MovementComponent : public Component {
    public:
        void init() override {
            pos = glm::vec3(1.0f);
            velocity = glm::vec3(0.0f);
            trans = glm::mat4(1.0f);
            mass = 10;
            speed = 100;
            speedMod = 1;
            dt = 0;
            scale = 150.0f;
            trans = glm::scale(trans, glm::vec3(scale));
        }

        void update() override {
            movement = mov.calcBehaviour(trans, dt, mass, speedMod, velocity, pos, mouseposX, mouseposY);
        }

        glm::mat4& move() { return movement; }
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
        void mouseX(double x) { mouseposX = x; }
        void mouseY(double y) { mouseposY = y; }

    private:
        Physics::Movement mov;
        glm::mat4 trans;
        glm::mat4 movement;
        glm::vec3 pos;
        glm::vec3 velocity;
        float mass;
        float dt;
        float scale;
        int speed;
        int speedMod;
        double mouseposX;
        double mouseposY;
};