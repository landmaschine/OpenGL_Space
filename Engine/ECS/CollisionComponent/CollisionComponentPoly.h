#pragma once
#include "../depComponents.h"
#include "../PositionComponent.h"

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
                    updatePolygonPosition(deltaPos);
                    initialPos = newPos;
                }
            }
            //polyData.print(polygon);
        }


    PolyData polygon;
    private:

        void updatePolygonPosition(const glm::vec3& deltaPos) {
            //for(auto& polygon : polygon.Polygons) {
                    //polygon.x += deltaPos.x;
                    //polygon.y += deltaPos.y;
            //}
        }

    glm::vec3 initialPos;
    PolyFromTxt polyData;
    glm::vec3 pos;
};