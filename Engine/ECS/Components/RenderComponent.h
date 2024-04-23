#pragma once
#include "../ECS.h"
#include "Engine/Pyhsics/physics.h"
#include <glm/glm.hpp>
#include "Engine/RenderEngine/Window/window.h"

class RenderComponent : public Component {
    public:
        void init() override {
            trans = glm::mat4(1.0f);
            rotMat = glm::mat4(1.0f);
            model = glm::mat4(1.0f);

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0); 
            glBindVertexArray(0);
        }

        void setPos(glm::vec4 _pos) {
            pos = _pos;
        }

        void getShaderID(unsigned int ID) { shaderID = ID; }

        glm::mat4& getModelMat() { return model; } 
        glm::mat4& transform() { return trans; }
        glm::mat4& rotTransforms() { return rotMat; }

        void update() override {
            //dont change -> beahviour of this multiplication is wanted
            model = rotMat * trans;
        }

        void draw() override {
            unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        glm::vec3 Pos() const {
            glm::vec3 position(0.0f);
            for (int i = 0; i < 4; ++i) {
                glm::vec3 vertexPosition = glm::vec3(model * glm::vec4(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2], 1.0f));
                position += vertexPosition;
            }
            position /= 4.0f;
            return position;
        }

        ~RenderComponent() override {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }

    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        unsigned int shaderID;
        glm::vec2 pos;
        glm::mat4 trans;
        glm::mat4 rotMat;
        glm::mat4 model;

        float vertices[12] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
           -0.5f, -0.5f, 0.0f,
           -0.5f,  0.5f, 0.0f 
        };
        unsigned int indices[6] = {
            0, 1, 3,
            1, 2, 3
        };  
};