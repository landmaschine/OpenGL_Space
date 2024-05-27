#pragma once
#include "../PositionComponent.h"
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
        unsigned int VBO, EBO;
        PolyFromTxt polydata;
        PolyData polygons;
        std::vector<float> vertices;
};