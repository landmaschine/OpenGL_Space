#pragma once
#include "depComponents.h"
#include "Engine/ECS/ECS.h"
#include "Engine/math/math.h"
#include "Engine/ECS/InputComponent.h"

class PhysicsComponent : public Component {
    public:
        PhysicsComponent() {}
        PhysicsComponent(playerData* data) {
            pos = data->pos;
            _accelSpeed = data->accelSpeed;
            body.damping = data->damping;
            body.mass = data->mass;
            body.currentPos = data->pos;
            body.previousPos = data->pos;
            body.isAwake = data->awake;
            body.isStatic = data->Static;
            body.inertia = data->inertia;
            body.angularDamping = data->angularDamping;
        }

        PhysicsComponent(colliderData* data) {
            pos = data->pos;
            body.damping = data->damping;
            body.mass = data->mass;
            body.currentPos = data->pos;
            body.previousPos = data->pos;
            body.isAwake = data->awake;
            body.isStatic = data->Static;
            body.inertia = data->inertia;
            body.angularDamping = data->angularDamping;
        }

        void init() override {
            _direction = glm::vec3(0.0f);
            velocity = glm::vec2(0.0f);
            trans = glm::mat4(1.0f);
            finaltrans = glm::mat4(1.0f);
            body.acceleration = glm::vec4(1.0f);
        }

        void update() override {
            if(entity->hasComponent<PositionComponent>()) {
                entity->getComponent<PositionComponent>().pos = glm::vec3(body.currentPos, 0.0f);
                entity->getComponent<PositionComponent>().prevPos = glm::vec3(body.previousPos, 0.0f);
                body.rotmat = entity->getComponent<PositionComponent>().rota;
            }

            if(entity->hasComponent<InputComponent>()) {
                body.force = entity->getComponent<InputComponent>().force;
                body.currentAngle = entity->getComponent<InputComponent>().angle;
            }

            body.inverserotmat = glm::inverse(body.rotmat);
        }

        glm::vec2 direction() {
            return _direction;
        }

        float accelSpeed() {
            return _accelSpeed;
        }

        glm::vec2 velocity = glm::vec2(0.f);
        RigidBody body;
        glm::mat4 trans = glm::mat4(1.0f);
        float torque = 0.1f;
    private:
        glm::vec2 _direction;
        glm::mat4 finaltrans = glm::mat4(1.0f);
        glm::vec3 pos;
        float _accelSpeed;
};