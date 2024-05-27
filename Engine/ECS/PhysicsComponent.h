#pragma once
#include "depComponents.h"
#include "Engine/ECS/ECS.h"
#include "InputComponent.h"

class PhysicsComponent : public Component {
    public:
        PhysicsComponent() {}
        PhysicsComponent(playerData* data) {
            pos = data->pos;
            maxSpeed = data->maxSpeed;  
            _direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            finaltrans = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
            speedMod = data->speedMod;
            _accelSpeed = data->accelSpeed;
            body.acceleration = glm::vec4(1.0f);
            body.damping = data->damping;
            body.Mass(data->mass);
            body.currentPos = data->pos;
            body.previousPos = data->pos;
            body.isAwake = data->awake;
            body.isStatic = data->Static;
        }

        PhysicsComponent(colliderData* data) {
            pos = data->pos;
            _direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            finaltrans = glm::mat4(1.0f);
            rota = glm::mat4(1.0f);
            body.acceleration = glm::vec4(1.0f);
            body.damping = data->damping;
            body.Mass(data->mass);
            body.currentPos = data->pos;
            body.previousPos = data->pos;
            body.isAwake = data->awake;
            body.isStatic = data->Static;
        }

        void init() override {
            
        }

        void update() override {
            if(entity->hasComponent<PositionComponent>()) {
                mousepos.x = entity->getComponent<PositionComponent>().mouseX;
                mousepos.y = entity->getComponent<PositionComponent>().mouseY;
                entity->getComponent<PositionComponent>().pos = pos;
            }

            if(entity->hasComponent<InputComponent>()) {
                _direction = entity->getComponent<InputComponent>().direction;
            }
        }

        glm::vec2 mousePos() {
            return mousepos;
        }

        glm::vec2 direction() {
            return _direction;
        }

        float accelSpeed() {
            return _accelSpeed;
        }

        glm::vec2 velocity = glm::vec2(0.f);
        RigidBody body;
        glm::vec2 force = glm::vec2(0.f);
    private:
        glm::vec2 _direction;
        glm::vec2 mousepos = glm::vec2(1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 rota = glm::mat4(1.0f);
        glm::mat4 finalRota = glm::mat4(1.0f);
        glm::mat4 finaltrans = glm::mat4(1.0f);
        glm::vec3 pos;
        int speedMod;
        float _accelSpeed;
        double maxSpeed;
};