#pragma once
#include <vector>
#include <memory>
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/RenderComponent.h"
#include "Engine/RenderEngine/OpenGL/Renderer.h"
#include "Engine/ECS/CollisionComponentPoly.h"

#include "Engine/Tools/utils.h"

class RenderSystem : public System {
    public:
        RenderSystem() {
            shader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/Systems/RenderSystem/renderVertex.vs", 
                              "/home/leonw/Documents/dev/OpenGL_Space/Engine/ECS/Systems/RenderSystem/renderFragment.fs");

            hitboxShader.loadShader("/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/HitBoxRender/hitboxVertex.vs", 
                                    "/home/leonw/Documents/dev/OpenGL_Space/Engine/RenderEngine/HitBoxRender/hitboxFragment.fs");

            renderer.init();
        }

        void render(Icamer2D& cam, bool renderhitbox, std::vector<std::unique_ptr<Entity>>& entities) override;

    private:
        void renderHitbox(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities);
        void renderTex(Icamer2D& cam, std::vector<std::unique_ptr<Entity>>& entities);
        Shader shader;
        Shader hitboxShader;
        Renderer renderer;
};