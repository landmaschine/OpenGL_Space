#pragma once
#include "../depComponents.h"
#include "../PositionComponent.h"
#include "HitBoxRender.h"

class CollisionComponentPoly : public Component {
    public:
        CollisionComponentPoly() {}
        CollisionComponentPoly(playerData* data) {
            polyData.extractConPolygonsFromTextFile(data->collision, &polygon);
            render.init(polygon);
        }

        CollisionComponentPoly(background* data) {
            polyData.extractConPolygonsFromTextFile(data->collision, &polygon);
            render.init(polygon);
        }
        
        void draw() override {
            render.render(view, projection, transform);
        }

        void cam(Icamer2D& cam) {
            projection = cam.projection();
            view = cam.view();
        }
        
        void init() override {
            if(entity->hasComponent<PositionComponent>()) {
                transform = entity->getComponent<PositionComponent>().transform;
            } else {
                std::cout << "ERROR entity has CollisionComponentPoly but no PositionComponent" << std::endl;
            }
            render.setpolygons(polygon);
        }

        void update(float dt) override {
            if(entity->hasComponent<PositionComponent>()) {
                transform = entity->getComponent<PositionComponent>().transform;
            }
        }

    PolyData polygon;
    private:
    HitBoxRender render;
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 transform = glm::mat4(1.0f);
    PolyFromTxt polyData;
};