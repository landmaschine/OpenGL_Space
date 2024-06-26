#pragma once
#include "Engine/ECS/depComponents.h"

#include "Engine/ECS/PositionComponent.h"
#include "Engine/ECS/InputComponent.h"
#include "Engine/Camera/Camera.h"
#include "lib/stb/stb_image.h"

class RenderComponent : public Component {
    public:
        RenderComponent() {}

        RenderComponent(std::string texturePath) {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int nrChannels;
            unsigned char* data = stbi_load(texturePath.c_str(), &m_width, &m_height, &nrChannels, 0);
            if(data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }

            if (GLAD_GL_EXT_texture_filter_anisotropic) {
                GLfloat largest;
                glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
            }
            stbi_image_free(data);
        }

        void init() override {
            model = glm::mat4(1.0f);
        }

        void update() override {
            if(entity->hasComponent<PositionComponent>()) {
                model = entity->getComponent<PositionComponent>().transform;
            }
            if(entity->hasComponent<InputComponent>()) {
                model = entity->getComponent<PositionComponent>().transform * entity->getComponent<PositionComponent>().rota;
            }
        }

        ~RenderComponent() override {}

        glm::mat4 model;
        unsigned int VAO;
        unsigned int texture;
    private:
        unsigned int m_VBO, m_EBO;

        int m_width, m_height;
        float m_vertices[20] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
           -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
           -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        unsigned int m_indices[6] = {  
            0, 1, 3,
            1, 2, 3
        };
};