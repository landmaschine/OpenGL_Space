#pragma once
#include "Components.h"

class PlayerMovementComponent : public Component {
    public:
        void init() override {
            pos = glm::vec3(1.0f);
            direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
            mass = 2.f;
            speedMod = 1;
            scale = 1.f;
            trans = glm::scale(trans, glm::vec3(scale));
            trans = glm::rotate(trans, -glm::radians(90.f), glm::vec3(1.0f, 0.0f, 0.0f));
        }

        void update(float dt) override {
            movement = mov.calcBehaviour(trans, rota, dt, mass, speedMod, direction, pos, velocity, mouseposX, mouseposY);
        }

        glm::mat4& move() { return movement; }
        glm::vec3& Pos() { return pos; }
        glm::vec3& getVel() { return direction; }
        float& getMass() { return mass; }
        int& getSpeedMod() { return speedMod; }
        void setX_pos(float _x) { pos.x = _x; }
        void setY_pos(float _y) { pos.y = _y; }
        void setX_vel(float _x) { direction.x = _x; }
        void setY_vel(float _y) { direction.y = _y; }
        void mouseX(double x) { mouseposX = x; }
        void mouseY(double y) { mouseposY = y; }

    private:
        Physics::Movement mov;
        glm::mat4 trans;
        glm::mat4 rota;
        glm::mat4 movement;
        glm::vec3 pos;
        glm::vec3 direction;
        glm::vec2 velocity;
        float mass;
        float scale;
        int speedMod;
        double mouseposX;
        double mouseposY;
};