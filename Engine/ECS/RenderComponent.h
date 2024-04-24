#pragma once
#include "Components.h"
#include "lib/stb/stb_image.h"
#include "Engine/RenderEngine/Shaders/shader.h"

class RenderComponent : public Component {
    public:
        void init() override {
            trans = glm::mat4(1.0f);
            rotMat = glm::mat4(1.0f);
            model = glm::mat4(1.0f);
            texture = 0;

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            data = stbi_load("/home/leonw/Documents/dev/OpenGL_Space/Engine/textures/SpaceSphipV2.png", &width, &height, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);


        }

        void update() override {
            //dont change -> behaviour of this multiplication is wanted
            model = rotMat * trans;
        }

        void draw() override {
            glBindTexture(GL_TEXTURE_2D, texture);
            
            glUseProgram(shaderID);
            unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        ~RenderComponent() override {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }

        glm::mat4& getModelMat() { return model; } 
        glm::mat4& transform() { return trans; }
        glm::mat4& rotTransforms() { return rotMat; }
        void getShaderID(unsigned int ID) { shaderID = ID; }
        glm::vec3& Pos() {return pos;}

    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        unsigned int shaderID;
        unsigned int texture;
        int width, height, nrChannels;
        unsigned char *data;
        glm::vec3 pos;
        glm::mat4 trans;
        glm::mat4 rotMat;
        glm::mat4 model;

        float vertices[32] = {
            //position              //color            //texture
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f 
        };

        unsigned int indices[6] = {  
            0, 1, 3,
            1, 2, 3
        };
};