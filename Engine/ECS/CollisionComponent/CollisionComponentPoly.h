#pragma once
#include "../depComponents.h"
#include "../PositionComponent.h"
#include "HitBoxRender.h"

class CollisionComponentPoly : public Component {
    public:
        CollisionComponentPoly() {}
        CollisionComponentPoly(playerData* data) {
            polyData.extractHullPolygonsFromTextFile(data->collision, &polygon);
            //HitBoxRender render(polygon, entity->getComponent<MovementComponent>());
            //polyData.print(polygon);
        }

        CollisionComponentPoly(background* data) {
            polyData.extractHullPolygonsFromTextFile(data->collision, &polygon);
        }
        
        void draw() override {
            
        }

        void cam(Icamer2D& cam) {}
        
        void init() override {
            if(entity->hasComponent<PositionComponent>()) {
                pos = entity->getComponent<PositionComponent>().pos;
            } else {
                std::cout << "ERROR entity has CollisionComponentPoly but no PositionComponent" << std::endl;
            }
        }

        void update(float dt) override {
            if(entity->hasComponent<PositionComponent>()) {
                auto newPos = entity->getComponent<PositionComponent>().pos;
                glm::vec3 deltaPos = newPos - initialPos;
                if(deltaPos != glm::vec3(0.0f)) {
                    initialPos = newPos;
                }
            }
            //polyData.print(polygon);
        }


    PolyData polygon;
    private:
    HitBoxRender render;
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    glm::vec3 initialPos;
    PolyFromTxt polyData;
    glm::vec3 pos;
};