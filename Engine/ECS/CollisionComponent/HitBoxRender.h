#pragma once
#include "../MovementComponent.h"

class HitBoxRender {
    public:
        HitBoxRender();
        HitBoxRender(PolyData poly, MovementComponent& move);
        ~HitBoxRender();
    private:
        unsigned int VAO, VBO;
        std::vector<float> vertices;
        Shader shader;
        PolyFromTxt polydat;
};