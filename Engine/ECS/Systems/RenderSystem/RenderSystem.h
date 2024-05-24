#pragma once 
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/RenderComponent/RenderComponent.h"
#include "Engine/RenderEngine/OpenGL/Renderer.h"

class RenderSystem : public System {
    public:
        RenderSystem() {
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/Systems/RenderSystem/renderVertex.vs", 
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/Systems/RenderSystem/renderFragment.fs");
            renderer.init();
        }

        void render(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities) override {
            renderer.render();
            for(auto& e : entities) {
                if(e->hasComponent<RenderComponent>()) {
                    shader.use();
                    shader.setMat4("model", e->getComponent<RenderComponent>().model);
                    shader.setMat4("projection", cam.projection());
                    shader.setMat4("view", cam.view());

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, e->getComponent<RenderComponent>().texture);
                    glBindVertexArray(e->getComponent<RenderComponent>().VAO);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                }
            }
        }

    private:
        Shader shader;
        Renderer renderer;
};