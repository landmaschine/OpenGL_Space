#pragma once
#include "Components.h"
#include "lib/stb/stb_image.h"
#include "Engine/RenderEngine/Shaders/shader.h"
#include "Engine/Models/Model.h"

class RenderComponent : public Component {
    public:
        void init() override {
            model = glm::mat4(1.0f);
        }

        void update(float dt) override {

        }

        void draw() override {
            glUseProgram(shaderID);
            unsigned int modelLoc = glGetUniformLocation(shaderID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            mdl.Draw(shaderID);
        }

        ~RenderComponent() override {

        }

        void setTex(std::string path) {
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
        }

        void setModel(std::string modelPath) {
            mdl.load(modelPath);
        }

        glm::mat4& getModelMat() { return model; } 
        void getShaderID(unsigned int ID) { shaderID = ID; }

    private:
        unsigned int shaderID;
        int width, height, nrChannels;
        glm::mat4 model;
        Model mdl;
};