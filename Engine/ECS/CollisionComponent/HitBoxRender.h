#pragma once
#include "../PositionComponent.h"
#include "Engine/Camera/Camera.h"

class HitBoxRender {
    public:
        HitBoxRender();
        HitBoxRender(PolyData poly);
        ~HitBoxRender();
        void render(Icamer2D& cam, PositionComponent& pos);
    private:
        unsigned int VAO, VBO, EBO;
        Shader shader;
        PolyFromTxt polydat;
        
    float vertices[12] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[6] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
};