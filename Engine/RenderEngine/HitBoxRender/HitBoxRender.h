#pragma once
#include "ECS/depComponents.h"
#include "Engine/Camera/Camera.h"

class HitBoxRender {
    public:
        HitBoxRender();
        ~HitBoxRender();
        void init();
        void setpolygons(PolyData polygons);
        
        unsigned int VAO;
        std::vector<unsigned int> indices;
    private:
        unsigned int m_VBO, m_EBO;
        PolyFromTxt m_polydata;
        PolyData m_polygons;
        std::vector<float> m_vertices;
};