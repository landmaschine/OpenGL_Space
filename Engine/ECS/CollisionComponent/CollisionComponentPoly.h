#pragma once
#include "../depComponents.h"
#include "../PositionComponent.h"
#include "../MovementComponent.h"
#include "HitBoxRender.h"
#include "Engine/Tools/utils.h"

class CollisionComponentPoly : public Component {
    public:
        CollisionComponentPoly() {}
        CollisionComponentPoly(playerData* data) {
            polyData.extractConPolygonsFromTextFile(data->collision, &polygon);
            originalPolygons = polygon;
            render.init(polygon);
        }

        CollisionComponentPoly(background* data) {
            polyData.extractConPolygonsFromTextFile(data->collision, &polygon);
            originalPolygons = polygon;
            render.init(polygon);
        }
        
        void draw() override {
            if(shouldrender) {
                render.render(view, projection, transform);
            }
        }

        void cam(Icamer2D& cam) {
            projection = cam.projection();
            view = cam.view();
        }
        
        void init() override {
            if(entity->hasComponent<PositionComponent>()) {
                transform = entity->getComponent<PositionComponent>().transform;
                pos = entity->getComponent<PositionComponent>().pos;
            } else {
                std::cout << "ERROR entity has CollisionComponentPoly but no PositionComponent" << std::endl;
            }
            render.setpolygons(polygon);

        }

        void update(float dt) override {

            if(entity->hasComponent<MovementComponent>()) {
                transform = entity->getComponent<MovementComponent>().finaltrans;
                rota = entity->getComponent<MovementComponent>().finalRota;
                pos = utils::extractTranslation(transform);
            } else if(entity->hasComponent<PositionComponent>()) {
                pos = entity->getComponent<PositionComponent>().pos;
            }

            if(pos != prevPos) {
                prevPos = pos;
            }

            for(size_t i = 0; i < polygon.Polygons.size(); ++i) {
                auto& p = polygon.Polygons[i];
                auto& originalP = originalPolygons.Polygons[i];
                for(size_t j = 0; j < p.size(); ++j) {
                    auto& v = p[j];
                    auto& originalV = originalP[j];

                    glm::vec3 rotatedVertex = rota * glm::vec4(originalV.x, originalV.y, 0.0f, 1.0f);
                    v.x = rotatedVertex.x + pos.x;
                    v.y = rotatedVertex.y + pos.y;
                }
            }
        }

    PolyData polygon;
    bool shouldrender = false;
    private:
    HitBoxRender render;
    glm::vec3 prevPos = glm::vec3(0.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 rota = glm::mat4(1.0f);
    PolyFromTxt polyData;
    PolyData originalPolygons;
    glm::vec3 pos = glm::vec3(0.f);
};