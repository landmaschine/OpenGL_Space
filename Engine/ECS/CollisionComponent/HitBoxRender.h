#pragma once
#include "../PositionComponent.h"
#include "Engine/Camera/Camera.h"

class HitBoxRender {
    public:
        HitBoxRender();
        ~HitBoxRender();
        void init(PolyData poly);
        void render(glm::mat4 view, glm::mat4 projection, glm::mat4 transform);
        void setpolygons(PolyData polygons);
    private:
        unsigned int VAO, VBO, EBO;
        Shader shader;
        PolyFromTxt polydata;
        PolyData polygons;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};