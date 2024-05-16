#pragma once
#include "Engine/ECS/depComponents.h"

#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/MovementComponent.h"
#include "Engine/Camera/Camera.h"
#include "lib/stb/stb_image.h"

class RenderComponent : public Component {
    public:
        RenderComponent() {}

        RenderComponent(std::string texturePath) {
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/OpenGL/renderVertex.vs", 
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/OpenGL/renderFragment.fs");

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            int nrChannels;
            unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
            if(data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            shader.use();
            shader.setInt("tex", 0);
        }

        void init() override {
            model = glm::mat4(1.0f);
            if(!entity->hasComponent<PositionComponent>()) {
                entity->addComponent<PositionComponent>();
            }
        }

        void update(float dt) override {
            if(entity->hasComponent<MovementComponent>()) {
                model = entity->getComponent<MovementComponent>().finaltrans;
            } else {
                model = entity->getComponent<PositionComponent>().transform;
            }
        }

        void cam(Camera2D* cam) {
            view = cam->getViewMatrix();
            projection = cam->getProjectionMatrix();
        }

        void draw() override {
            shader.use();
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);
            shader.setMat4("model", model);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        ~RenderComponent() override {

        }

        glm::mat4 model;
        unsigned int texture;
        unsigned int VBO, VAO, EBO;
        Shader shader;
    private: 
        int width, height;
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);

        float vertices[20] = {
            // positions       // texture coords
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
           -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top left 
        };

        unsigned int indices[6] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
};