#pragma once
#include "depComponents.h"
#include "PositionComponent.h"
#include "Engine/RenderEngine/HitBoxRender/HitBoxRender.h"
#include "Engine/Tools/utils.h"

class CollisionComponentPoly : public Component {
    public:
        CollisionComponentPoly() {}
        CollisionComponentPoly(playerData* data) {
            m_polyData.extractConPolygonsFromTextFile(data->collision, &polygon);
            m_polyData.scalePolygons(data->scale, polygon);
            m_originalPolygons = polygon;
            render.init();
            render.setpolygons(polygon);
        }

        CollisionComponentPoly(colliderData* data) {
            m_polyData.extractConPolygonsFromTextFile(data->collision, &polygon);
            m_polyData.scalePolygons(data->scale, polygon);
            m_originalPolygons = polygon;
            render.init();
            render.setpolygons(polygon);
        }
        
        void init() override {
            if(entity->hasComponent<PositionComponent>()) {
                transform = entity->getComponent<PositionComponent>().transform;
                m_rota = entity->getComponent<PositionComponent>().rota;
                m_pos = utils::extractTranslation(transform);
            } else {
                std::cout << "ERROR entity has CollisionComponentPoly but no PositionComponent" << std::endl;
            }
        }

        void update() override {
            if(entity->hasComponent<PositionComponent>()) {
                transform = entity->getComponent<PositionComponent>().transform;
                m_rota = entity->getComponent<PositionComponent>().rota;
                m_pos = utils::extractTranslation(transform);
            }

            if(m_pos != m_prevPos) {
                m_prevPos = m_pos;
            }

            for(size_t i = 0; i < polygon.Polygons.size(); ++i) {
                auto& p = polygon.Polygons[i];
                auto& originalP = m_originalPolygons.Polygons[i];
                for(size_t j = 0; j < p.size(); ++j) {
                    glm::vec3 rotatedVertex = m_rota * glm::vec4(originalP[j].x, originalP[j].y, 0.0f, 1.0f);
                    p[j].x = rotatedVertex.x + m_pos.x;
                    p[j].y = rotatedVertex.y + m_pos.y;
                }
            }
            render.setpolygons(polygon);
        }

    PolyData polygon;
    bool shouldrender = false;
    glm::mat4 transform = glm::mat4(1.0f);
    HitBoxRender render;
    private:
        glm::vec3 m_prevPos = glm::vec3(0.0f);
        glm::mat4 m_projection = glm::mat4(1.0f);
        glm::mat4 m_view = glm::mat4(1.0f);
        glm::mat4 m_rota = glm::mat4(1.0f);
        PolyFromTxt m_polyData;
        PolyData m_originalPolygons;
        glm::vec3 m_pos = glm::vec3(0.f);
};